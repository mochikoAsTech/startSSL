= SSL証明書を取ってHTTPSでサイトを見よう

ウェブサーバとドメイン名を用意したらHTTPでサイトが見られました。

今度はHTTPSでサイトを見るために、SSL証明書を取得しましょう。

//pagebreak

== SSL証明書にまつわる登場人物

SSL証明書は、関わってくるファイルが多いので、最初に登場人物をご紹介します。

 * 秘密鍵（startssl.key）
 * CSR（startssl.csr）
 * SSL証明書（ssl.自分のドメイン名.crt）
 * 中間CA証明書（ca-bundle.ca）
 * SSL証明書＋中間CA証明書（startssl.crt）

次のような流れでSSL証明書を取得して、HTTPSのサイトを作ります。

 1. サーバで秘密鍵を作る
 2. 秘密鍵からCSR（証明書署名リクエスト）を作る
 3. CSRを認証局に渡してSSL証明書の発行を依頼
 4. TXTレコードを作ってDNS認証
 5. メールでSSL証明書と中間CA証明書が届く
 6. SSL証明書と中間CA証明書をサーバにアップして1ファイルにまとめる
 7. NGINXでHTTPSのバーチャルホストを作る

流れも複雑なので、どこに何のファイルを置いたか分からなくなってしまわないよう、登場人物が集まる場所として、サーバの中で@<code>{/etc/nginx/}の下に@<code>{ssl}というディレクトリを作っておきましょう。@<fn>{error}

//footnote[error][もし@<code>{mkdir: cannot create directory '/etc/nginx/ssl': Permission denied}と表示されてしまったら、あなたはいま、うっかり一般ユーザのままでmkdirコマンドを実行しています。コマンドの例で、左側のプロンプトが「#」のときは、rootで実行してください。「sudo su -」と書いてEnterキーを押すとrootになれます]

//cmd{
# mkdir /etc/nginx/ssl/
# cd /etc/nginx/ssl/
//}

== 秘密鍵（startssl.key）を作ろう

最初に作成するのが秘密鍵@<fn>{secret}です。秘密鍵は「.key」や「.pem」@<fn>{pem}という拡張子で作成されることが多いです。秘密鍵は名前のとおり「秘密」にすべきです。つまり、限られた人だけが触れるように管理すべきですので、決してメールに添付して送ったり、サーバ内でどのユーザでも見られる場所に置いたりしてはいけません。

//footnote[secret][さっき作ったのはSSHでログインするための秘密鍵で、今から作るのはSSL証明書を取得するための秘密鍵なので別物です]
//footnote[pem][秘密鍵がPEMと呼ばれるテキスト形式で生成されることから、pemという拡張子が使われるようです]

それでは次のopensslコマンドをたたいて、秘密鍵を生成しましょう。左から順に「opensslコマンドで／鍵アルゴリズムがRSAの秘密鍵を作る／秘密鍵は/etc/nginx/ssl/以下にstartssl.keyというファイル名で保存する／鍵の長さは2048ビット」という意味です。できあがった秘密鍵は、chmodコマンドで読み書き権限を厳しくしておきます。

//cmd{
# openssl genrsa -out /etc/nginx/ssl/startssl.key 2048
Generating RSA private key, 2048 bit long modulus
...........................................................................................+++
...........................+++
e is 65537 (0x10001)

# chmod 600 /etc/nginx/ssl/startssl.key
//}

できあがった秘密鍵を、catコマンドで見てみましょう。

//cmd{
# cat /etc/nginx/ssl/startssl.key
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA0+s/GzdbObzg6QWzCvK5JofMv6izHzlCfMCMhcU7SeBd2tHN
icRA7g5CZq09aaEqv1949cFX5C3bgHxl4O+epeudrKyUjRwZSpS7OmznDBFQByTY
（中略）
InsCw9qu+iZknMKiISw3Krht/898/hq0jqLFJUTbfg9BP8w+JVW4+8hp4OSklymc
NRcvPYUBQy3wK+w527rksodkGZ77c6Q+XxRtH/wpo3H+xwhmJvi+T2o=
-----END RSA PRIVATE KEY-----
//}

===[column] 【コラム】SSL証明書の秘密鍵にパスフレーズは設定すべき？

opensslコマンドで秘密鍵を作るとき、-aes128や-aes256というオプションを付けると、パスフレーズを聞かれて、指定の暗号方式で暗号化された秘密鍵が出力されます。@<fn>{option}
このとき、［Enter pass phrase:］や［Verifying - Enter pass phrase:］と表示された横で、いくらキーボードをたたいて文字を入力しても、黒い画面上は何も表示されません。ですが、ちゃんと文字入力はできているので大丈夫です。入力を間違えたら、Backspaceキーで消して書き直すこともできます。

//cmd{
# openssl genrsa -aes128 -out /etc/nginx/ssl/with-passphrase.key 2048
Generating RSA private key, 2048 bit long modulus
（中略）
Enter pass phrase:    ←秘密鍵のパスフレーズとして「startssl」と入力
Verifying - Enter pass phrase:    ←もう一度「startssl」と入力
//}

SSHの鍵ペアを作ったときのコラムでも解説しましたが、秘密鍵がパスフレーズで保護されていると、秘密鍵を盗んだ誰かが使おうとしても、パスフレーズが分からなければ使えないので安心です。

しかし秘密鍵にパスフレーズが設定されていると、ApacheやNGINXといったウェブサーバを再起動した際にも、必ずパスフレーズを聞かれます。もし何かトラブルがあってサーバがOSごと再起動してしまった場合、折角NGINXが自動起動する設定になっていても、パスフレーズを聞くところで止まって起動できず、サイトが自動復旧しない、というトラブルが発生します。

このトラブルを回避するには、パスフレーズをファイルに書いておいて、NGINXの自動起動時にそれを読み込むようにする、という方法があります。しかし折角設定したパスフレーズをファイルに書いて同じウェブサーバ内に置いてしまうと、秘密鍵を盗むとき、一緒にパスフレーズのファイルも盗まれてしまう可能性が高くなり、もはやパスフレーズを設定した意味がありません。そのため筆者は、ウェブサーバに設置して使う秘密鍵にはパスフレーズは設定しなくてよい、という考えです。

ちなみに、次のように一度パスフレーズありで作った秘密鍵を、パスフレーズなしで複製することも可能です。

//cmd{
# cd /etc/nginx/ssl/
# openssl rsa -in with-passphrase.key -out without-passphrase.key
Enter pass phrase for with-passphrase.key:    ←秘密鍵のパスフレーズ「startssl」を入力
writing RSA key
//}

利便性を保ちつつ安全性も向上させたければ、本番のウェブサーバで使う秘密鍵はパスフレーズなし、バックアップとして他のサーバで保管しておく秘密鍵はパスフレーズありにしておく、という方法がいいでしょう。

===[/column]

//footnote[option][さっきは-aes128や-aes256といった「どの暗号で暗号化するか？」のオプションを何も指定しなかったので、パスフレーズは聞かれず、秘密鍵も暗号化されませんでした]

== CSR（startssl.csr）を作ろう

秘密鍵ができたら、続いてCSR（Certificate Signing Request）の作成に進みましょう。CSRは「.csr」という拡張子で作成されることが多いです。CSRは「Certificate Signing Request（証明書署名リクエスト）」という名前のとおり、認証局に対して「こういう内容でSSL証明書を作って署名してください」とリクエストする、申請書のようなものです。

次のopensslコマンドを実行します。左から順に、「opensslコマンドで／CSRを作る／新しく作る／元になる秘密鍵はstartssl.key／CSRはstartssl.csrというファイル名で作る」という意味です。

//cmd{
# cd /etc/nginx/ssl/
# openssl req -new -key startssl.key -out startssl.csr
//}

すると、CSRを作成するため、いくつか質問をされます。（@<table>{dn}）@<fn>{ou}コモンネームには、@<code>{ssl.自分のドメイン名}を入力してください。

//footnote[ou][本書ではDV証明書を取得するため「組織単位名（OU）」は任意としていますが、証明書の種類や認証局によっては必須のところもあるようです。取得時に認証局のサイトで確認しましょう。DV証明書については後述します]

//table[dn][CSR作成時に聞かれる質問]{
質問	説明	入力する内容の例	必須/任意
------------------------------------
Country Name	国名（C）	JP	必須
State or Province Name	都道府県名（S/ST）	Tokyo	必須
Locality Name	市町村名（L）	Shinjuku-ku	必須
Organization Name	組織名（O）	mochikoAsTech		必須
Organizational Unit Name	組織単位名（OU）	入力なし	任意
Common Name	コモンネーム（CN）	ssl.startdns.fun	必須
//}

//cmd{
Country Name (2 letter code) [XX]:JP
State or Province Name (full name) []:Tokyo
Locality Name (eg, city) [Default City]:Shinjuku-ku
Organization Name (eg, company) [Default Company Ltd]:mochikoAsTech
Organizational Unit Name (eg, section) []:
Common Name (eg, your name or your server's hostname) []:ssl.startdns.fun
//}

次の3つは入力不要です。

//cmd{
Email Address []:
A challenge password []:
An optional company name []:
//}

質問に全て答えると、CSRができあがります。再びopensslコマンドをたたいて、CSRの中身を見てみましょう。「Subject」と書かれた行を見て、生成されたCSRの内容が正しいか確認します。

//cmd{
# openssl req -text -in /etc/nginx/ssl/startssl.csr -noout | head -4
Certificate Request:
    Data:
        Version: 0 (0x0)
        Subject: C=JP, ST=Tokyo, L=Shinjuku-ku, O=mochikoAsTech, CN=ssl.startdns.fun
//}

内容に問題がなければ、CSRをcatコマンドで表示します。「-----BEGIN CERTIFICATE REQUEST-----」から「-----END CERTIFICATE REQUEST-----」までをコピーしたら、メモ帳にペーストしておきましょう。メモしたCSRはこの後使用します。

//cmd{
# cat /etc/nginx/ssl/startssl.csr 
-----BEGIN CERTIFICATE REQUEST-----
MIICqzCCAZMCAQAwZjELMAkGA1UEBhMCSlAxDjAMBgNVBAgMBVRva3lvMRQwEgYD
VQQHDAtTaGluanVrdS1rdTEWMBQGA1UECgwNbW9jaGlrb0FzVGVjaDEZMBcGA1UE
（中略）
jP1RMQS3PuYDE6QIVJ5zbMC+RIydSQ/0Dr9VUHWiYqDPjx+BpphYT5AxMwbw9/m5
noKGvJl1Mt7G03Awa/TX
-----END CERTIFICATE REQUEST-----
//}

=== 【ドリル】CSRで入力すべきなのは誰の情報？

==== 問題

A銀行のウェブサイトをHTTPSで作ることになりました。SSL証明書@<fn>{evSsl}の取得はA銀行の代わりに広告代理店のB社が行い、さらにサイトの制作や運用はA銀行からWeb制作会社のC社に委託する場合、CSRで入力する住所や会社名はA銀行・B社・C社のどれにすべきでしょうか？

 * A. A銀行のウェブサイトなんだからA銀行を入力すべき
 * B. A銀行から任されてSSL証明書を買うのはB社だからB社を入力すべき
 * C. 実際にサイトの管理を任されているのはC社だからC社を入力すべき

//footnote[evSsl][SSL証明書の種類は「EV証明書」とします。EV証明書については@<chapref>{05_ssl}で後述します]

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。ウェブサイトの運営元がA銀行であることを証明するためのSSL証明書なので、CSRではA銀行の情報を記載すべきです。

A銀行のフィッシングサイトが出てきたときに、ユーザが「本物のサイトか確認しよう」と思って証明書の情報を見て、B社やC社の情報が表示されたら「A銀行じゃない！」となってしまいます。

===[column] 【コラム】opensslコマンドのユーティリティ（道具）たち

@<chapref>{01_whatIsSsl}で説明したとおり、OpenSSLはSSLというプロトコル（約束事）に従って実装された、暗号処理のためのソフトウェアです。OpenSSLのコマンドラインツールであるopensslコマンドには、色々なユーティリティ（道具）が詰まっています。秘密鍵を作るときには@<code>{genrsa}、CSRを作るときには@<code>{req}というユーティリティを、opensslコマンドの引数につけて実行しましたよね。

//cmd{
秘密鍵を作るときは、genrsaというユーティリティを使った
# openssl genrsa -out /etc/nginx/ssl/startssl.key 2048

秘密鍵をパスフレーズありからなしにするときはrsaというユーティリティを使った
# openssl rsa -in with-passphrase.key -out without-passphrase.key

CSRを作るときは、reqというユーティリティを使った
# openssl req -new -key startssl.key -out startssl.csr
//}

@<code>{genrsa}や@<code>{req}、@<code>{rsa}の他に、どんなユーティリティがあるのか？は、@<code>{openssl help}@<fn>{help}で確認できます。

//cmd{
$ openssl help
openssl:Error: 'help' is an invalid command.

Standard commands
asn1parse         ca                ciphers           cms
crl               crl2pkcs7         dgst              dh
dhparam           dsa               dsaparam          ec
ecparam           enc               engine            errstr
gendh             gendsa            genpkey           genrsa
nseq              ocsp              passwd            pkcs12
pkcs7             pkcs8             pkey              pkeyparam
pkeyutl           prime             rand              req
rsa               rsautl            s_client          s_server
s_time            sess_id           smime             speed
spkac             ts                verify            version
x509              
//}

それぞれのユーティリティの使い方が知りたいときは、manコマンドの引数にユーティリティ名をつけてやれば、マニュアルが表示されます。

//cmd{
$ man genrsa
//}

===[/column]

//footnote[help][helpという存在しないユーティリティを指定してopensslコマンドを実行することで、ユーティリティの一覧が表示される、という仕組みです]

== SSL証明書の取得申請を出そう

それではターミナルは一旦置いておいて、ブラウザを開いてください。ここからはCSRに従って、認証局にSSL証明書を発行してもらいます。［FujiSSL］で検索して、［FujiSSL-安心・安全の純国産格安SSLサーバ証明書］をクリック（@<img>{startSSL_86}）します。@<fn>{fujissl}

//footnote[fujissl][検索すると色んな価格帯のSSL証明書が出てきますが、値段によって何が違うのかについては、@<chapref>{05_ssl}で後述します。本書ではFujiSSLという安価な証明書を取得します]

//image[startSSL_86][［FujiSSL-安心・安全の純国産格安SSLサーバ証明書］をクリック][scale=0.8]{
//}

右上の［お申し込みはこちら］をクリック（@<img>{startSSL_87}）します。

//image[startSSL_87][［お申し込みはこちら］をクリック][scale=0.8]{
//}

続いて［お申し込みサイト（ストアフロント）へ］をクリック（@<img>{startSSL_88}）します。

//image[startSSL_88][［お申し込みサイト（ストアフロント）へ］をクリック][scale=0.8]{
//}

指定された文書と「収集した個人情報の利用目的」を確認した上で、チェックボックスにチェックを入れて［次へ］をクリック（@<img>{startSSL_89}）します。

//image[startSSL_89][チェックを入れて［次へ］をクリック][scale=0.8]{
//}

クーポンコードは［使用しない］、申し込み種別は［新規申込み］、商品選択は［ドメイン認証］の［FujiSSL］になっていることを確認（@<img>{startSSL_90}）します。

//image[startSSL_90][クーポンコード、申し込み種別、商品選択を確認][scale=0.8]{
//}

下へスクロールして、お申込み年数が［FujiSSL 1年 1,100円］@<fn>{price}になっていることを確認（@<img>{startSSL_91}）したら、先ほどメモ帳にメモしておいたCSRを、［CSR］へ貼り付けます。「-----BEGIN CERTIFICATE REQUEST-----」から「-----END CERTIFICATE REQUEST-----」まで、丸ごとコピー＆ペーストしてください。

//footnote[price][2020年2月現在、FujiSSLの「ドメイン認証シングルタイプ」というSSL証明書は、有効期間1年で税込1,100円です]

//image[startSSL_91][CSRをペーストする][scale=0.8]{
//}

［次へ］をクリック（@<img>{startSSL_92}）してください。

//image[startSSL_92][［次へ］をクリック][scale=0.8]{
//}

［認証方式を選択］へ進みます。これは「@<ttb>{CSRのコモンネームで指定したドメイン名が、あなたの持ち物であることをどうやって証明しますか？}」ということを聞かれています。対象のドメイン名で、メールを受信してURLを踏む（メール認証）か、指定された内容のリソースレコードをDNSで追加する（DNS認証）か、指定された内容のファイルをウェブサイトにアップする（ファイル認証）か、いずれかの方法で「このドメイン名（筆者ならssl.startdns.fun）は私の持ち物です」ということを証明しなければいけません。

今回はDNSでTXTレコードを追加する、という方法で証明するので、［DNS認証］を選択（@<img>{startSSL_93}）して［次へ］をクリックします。

//image[startSSL_93][［DNS認証］を選択して［次へ］をクリック][scale=0.8]{
//}

今回購入するのはDV証明書です。DV証明書は「そのドメイン名の使用権があること」だけを証明してくれます。サイトの運営者が日本にいることや、東京の新宿区にオフィスがあること、mochikoAsTechという組織であることなどは確認も証明もしないので、実際の証明書にもそれらの情報は反映されません。（@<img>{startSSL_94}）

//image[startSSL_94][［証明書情報］は［コモンネーム］だけが反映される][scale=0.8]{
//}

［申請組織担当者情報］と［技術担当者情報］を英語表記で入力（@<img>{startSSL_95}）します。ここで入力した住所や電話番号、個人名などが外向けに公開されることはありませんので、安心して入力してください。@<fn>{evOrOv}

//footnote[evOrOv][EV証明書やOV証明書の場合は、ここで入力した担当者宛てに実在確認の連絡が入ります。詳細については@<chapref>{05_ssl}で後述します]

//image[startSSL_95][［申請組織担当者情報］と［技術担当者情報］を入力][scale=0.8]{
//}

ここで入力した［Eメールアドレス］宛てに、後でSSL証明書が送られてきます。メールアドレスを間違えないよう注意してください。すべて入力したら、［次へ］をクリック（@<img>{startSSL_96}）します。

//image[startSSL_96][［次へ］をクリック][scale=0.8]{
//}

［決済情報入力］に、SSL証明書代を支払うクレジットカード情報を入力（@<img>{startSSL_97}）します。

//image[startSSL_97][クレジットカード情報を入力][scale=0.8]{
//}

［書類送付先］で［請求書宛名］、［納品書宛名］、［領収書宛名］を記入したら、［上記の内容で注文を確定する］をクリック（@<img>{startSSL_98}）します。

//image[startSSL_98][［上記の内容で注文を確定する］をクリック][scale=0.8]{
//}

「注文を確定します。よろしいですか？」と表示（@<img>{startSSL_99}）されたら、［OK］をクリックします。

//image[startSSL_99][［OK］をクリック][scale=0.4]{
//}

「この内容で決済を確定します。よろしいですか？」と表示（@<img>{startSSL_100}）されます。「1年間有効なSSL証明書を1,100円で買うんだ！」というケツイ@<fn>{ketsui}をしたら、［OK］をクリックします。

//image[startSSL_100][1,100円払うケツイをして［OK］をクリック][scale=0.4]{
//}

//footnote[ketsui][UNDERTALEというゲームは、ゲームオーバーになるたび「ケツイを　ちからに　かえるんだ…！」というメッセージが表示されます。筆者はパピルスが好きですが、初見でうっかり殺してしまい、同僚に人でなし扱いされました]

［お申込み完了］のページが表示（@<img>{startSSL_101}）されました。

//image[startSSL_101][SSL証明書の申し込みが完了した！][scale=0.8]{
//}

先ほど登録したメールアドレス宛に、DNS設定情報を知らせるメールが届いていますので確認しましょう。

== DNSの設定をしよう

［@<code>{CommonName=ssl.自分のドメイン名}］から始まる件名のメール（@<img>{startSSL_102}）がすぐに届きます。例えばCSRのコモンネームで指定したドメイン名が［ssl.startdns.fun］だった場合、ベースドメイン名である［startdns.fun］のTXTレコードを追加して、メールに書いてある値を設定するよう書いてあります。

//image[startSSL_102][追加すべきTXTレコードの値がメールで届いた][scale=0.8]{
//}

例えば、そのドメイン名で使用しているネームサーバが「お名前.com」なら、DNS設定の画面で次のようにTXTレコードを追加（@<img>{startSSL_103}）します。今回はサブドメインを含まないドメイン名を追加するので、［ホスト名］には何も入力しません。［VALUE］には、メールに書いてあった値をそのままコピー＆ペーストします。

//image[startSSL_103][「自分のドメイン名」のTXTレコードを追加する][scale=0.6]{
//}

ちょっとだけ時間をおいてから、TXTレコードが追加されたか確認してみましょう。TXTレコードが追加されたかどうかは、次のdigコマンドで確認できます。digコマンドをたたいた結果、メールに書いてあった値が返ってくればTXTレコードは設定できています。

//cmd{
$ dig 自分のドメイン名 txt +short
//}

筆者の場合は、次のように表示されました。

//cmd{
$ dig startdns.fun txt +short
"20200204005703EA923DBFD3（中略）DD5B966ED7C2BB87C0386B17A076"
//}

これでTXTレコードの設定@<fn>{caa}は完了です。

//footnote[caa][いま設定したTXTレコードの他に、CAAレコードがSSL証明書の発行に関わってくることがあります。CAAレコードについては、「DNSをはじめよう」の「〈トラブル〉CAAレコードが原因でSSL証明書が発行できなかった」で説明しています]

== SSL証明書と中間CA証明書をメールで受け取ろう

TXTレコードを追加してから、おおよそ30分後にSSL証明書がメール（@<img>{startSSL_104}）で届きました。

//image[startSSL_104][SSL証明書がメールで届いた][scale=0.6]{
//}

メールに添付されているZIPファイル（@<code>{ssl.自分のドメイン名.zip}）にSSL証明書が入っていますのでダウンロードします。（@<img>{startSSL_105}）

//image[startSSL_105][メールに添付されているZIPファイルをダウンロード][scale=0.4]{
//}

Windowsの方もMacの方も、ダウンロードしたZIPファイルはデスクトップに置いてください。（@<img>{startSSL_106}）

//image[startSSL_106][ダウンロードしたZIPファイルはデスクトップに置く][scale=0.4]{
//}

ZIPファイルを右クリックして、［すべて展開］をクリックします。（@<img>{startSSL_107}）

//image[startSSL_107][右クリックして［すべて展開］をクリック][scale=0.3]{
//}

［展開］をクリックします。（@<img>{startSSL_108}）

//image[startSSL_108][［展開］をクリック][scale=0.4]{
//}

展開したフォルダ（@<img>{startSSL_109}）の中の［ssl.自分のドメイン名.crt］がSSL証明書で、［ca-bundle.ca］が中間CA証明書です。README.txtはファイルの説明書です。

//image[startSSL_109][ssl.自分のドメイン名.crtがSSL証明書で、ca-bundle.caが中間CA証明書][scale=0.4]{
//}

どちらも必要なものなので、これからSSL証明書と中間CA証明書の2つをサーバにアップロードしましょう。

== SSL証明書をサーバに設置しよう

それではSSL証明書をサーバに設置します。NGINXではSSL証明書と中間CA証明書の2つを、1ファイルにまとめて使用するので、まずはアップロードして、それから1ファイルにまとめる作業を行ないます。Windows、Macの順番で手順を説明します。

=== WindowsでSSL証明書と中間CA証明書をアップロードしよう

Windowsのパソコンを使っている方は、RLoginを起動します。［startSSLInstance］を選択して、［OK］をクリック（@<img>{startSSL_110}）します。

//image[startSSL_110][RLoginを起動して［startSSLInstance］を選択してログイン][scale=0.6]{
//}

黒い画面が開いたら、［ファイル］から［SFTPファイルの転送］をクリック（@<img>{startSSL_111}）します。

//image[startSSL_111][［ファイル］から［SFTPファイルの転送］をクリック][scale=0.6]{
//}

左側にあなたのパソコンのファイルが表示されていて、右側にサーバのファイルが表示されています。左側で、デスクトップに展開したフォルダ@<fn>{folder}を選択したら、［ssl.自分のドメイン名.crt］と［ca-bundle.ca］を右側にドラッグ＆ドロップ（@<img>{startSSL_112}）してください。これでサーバの「@<code>{/home/opc}」にファイルがアップロードされます。

//footnote[folder][筆者の場合は「C:\Users\mochikoAsTech\Desktop\ssl.startdns.fun」でした]

//image[startSSL_112][［ssl.自分のドメイン名.crt］と［ca-bundle.ca］を右側にドラッグ＆ドロップ][scale=0.6]{
//}

右側のサーバに［ssl.自分のドメイン名.crt］と［ca-bundle.ca］がアップロードされたら、×を押してファイル転送の画面は閉じて構いません。（@<img>{startSSL_113}）

//image[startSSL_113][［ssl.自分のドメイン名.crt］と［ca-bundle.ca］がサーバにアップされた][scale=0.6]{
//}

=== MacでSSL証明書と中間CA証明書をアップしよう

Macを使っている方は、ターミナルを起動してください。sshコマンドではなく、scpコマンドを使って、Macの中にある［ssl.自分のドメイン名.crt］と［ca-bundle.ca］を、サーバへアップロードします。［ZIPを展開したフォルダ］、［ssl.自分のドメイン名.crt］、［パブリックIPアドレス］の部分は、ご自身のものに書き換えてください。

//cmd{
$ cd ~/Desktop/ZIPを展開したフォルダ
$ scp -i ~/Desktop/startSSLKey ssl.自分のドメイン名.crt ca-bundle.ca opc@パブリックIPアドレス:/home/opc/
ssl.自分のドメイン名.crt    100%  0   0.0KB/s   00:00    
ca-bundle.ca               100%  0   0.0KB/s   00:00   
//}

=== 証明書を1ファイル（startssl.crt）にまとめよう

これでWindowsの方も、Macの方も、サーバにSSL証明書と中間CA証明書をアップロードできました。それではターミナルでサーバにログインして、先ほどアップロードした［ssl.自分のドメイン名.crt］と［ca-bundle.ca］が、ちゃんと「@<code>{/home/opc/}」以下に存在していることを確認しましょう。

//cmd{
$ sudo su -

# ls /home/opc/
ca-bundle.ca  ssl.自分のドメイン名.crt
//}

続いて2つのファイルから、新たに［startssl.crt］というファイルを作りましょう。@<fn>{awk}NGINXではSSL証明書と中間CA証明書という2つのファイルを、1つのファイルにがっちゃんこ！とつなげて使うためです。

//cmd{
# cd /etc/nginx/ssl/
# awk 1 /home/opc/ssl.自分のドメイン名.crt /home/opc/ca-bundle.ca > startssl.crt
//}

//footnote[awk][このときcatコマンドで結合すると、SSL証明書と中間CA証明書の間に改行が入らず、「-----END CERTIFICATE----------BEGIN CERTIFICATE-----」のようになってしまうため、awkコマンドを使います]

2つのファイルを1つにつなげたら、catコマンドで［startssl.crt］を確認してみましょう。次のように「-----BEGIN CERTIFICATE-----」と「-----END CERTIFICATE-----」が、繰り返し3つ表示されれば大丈夫@<fn>{order}です。

//footnote[order][1つのファイルにつなげるときには、SSL証明書が上で、中間CA証明書が下です。順番には意味があるので、逆にならないよう注意してください]

//cmd{
# cat /etc/nginx/ssl/startssl.crt
-----BEGIN CERTIFICATE-----
MIIF/DCCBOSgAwIBAgIQaoS/P1b4mCR8mn5/WUrI6zANBgkqhkiG9w0BAQsFADBn
MQswCQYDVQQGEwJKUDElMCMGA1UEChMcU0VDT00gVHJ1c3QgU3lzdGVtcyBDTy4s
（中略）
31pTIUPabkFxDPjslVw9c7z3Vgk2fnpuwE2lrE+46zrJ3oTRqsABDbYreK1a5vsG
tcnpUlL1hrk/rC3JuI2ttHVaHU+1JCgTSRpvO3a44azDy15T5C97dGxuowPgcaMQ
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIEpzCCA4+gAwIBAgIJIrmxVPM8Xl4AMA0GCSqGSIb3DQEBCwUAMF0xCzAJBgNV
BAYTAkpQMSUwIwYDVQQKExxTRUNPTSBUcnVzdCBTeXN0ZW1zIENPLixMVEQuMScw
（中略）
g3tiJAlFIpfXXD4cArZo6ZlXJ26B4H7vk5GmyR6poDy/CRvC7VIz3xp6o2348W1j
32S9pEuZhtxtMvPjnsHIWPNdz8pHv21x7bYwDnocwN2uk3QrrljxTQ9evg==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIEcjCCA1qgAwIBAgIJErmw+nLg2EjGMA0GCSqGSIb3DQEBCwUAMFAxCzAJBgNV
BAYTAkpQMRgwFgYDVQQKEw9TRUNPTSBUcnVzdC5uZXQxJzAlBgNVBAsTHlNlY3Vy
（中略）
u5ZuCjxerxj3qS1rM46bcEfjopnaD7hnJXSYiL1d0yw5zSW2PEe+LHdoIAb2I6D8
8UFJH0Cli6sY5l8jhjkOOs1yeu1C/RcY0+NBHKZkFEeEb6ez0sg=
-----END CERTIFICATE-----
//}

これで証明書ファイルの準備は完了です。

== NGINXでHTTPSのバーチャルホストを作ろう

「@<code>{/etc/nginx/conf.d/}」というディレクトリの下に移動して、もともとあった設定ファイルをmvコマンドでバックアップしておきます。

//cmd{
# cd /etc/nginx/conf.d/
# mv default.conf default.conf.backup
//}

viコマンドで、同じ場所に新しい設定ファイル@<fn>{nginxConf}を作ります。viコマンドでファイルを編集するときは、i（アイ）を押してから入力します。書き終わったらESCキーを押して、「:wq」と入力してEnterキーを押せば変更が保存されます。@<code>{ssl_ciphers}は、紙面上では途中で改行して4行になっていますが、実際は改行なしで1行です。

//footnote[nginxConf][設定ファイル（startssl.conf）を手入力するのがしんどい場合は、PDF版からコピー＆ペーストしても構いません。紙の本を購入された方は、PDF版を無料でダウンロードできます。ダウンロード方法は「あとがき」をご確認ください]

//cmd{
# vi startssl.conf

server {
    listen 80 default_server;
    return 301 https://$host$request_uri;
}

server {
    listen       443 ssl http2;
    server_name  ssl.startdns.fun;

    # 秘密鍵
    ssl_certificate_key /etc/nginx/ssl/startssl.key;
    # SSL証明書＋中間CA証明書
    ssl_certificate     /etc/nginx/ssl/startssl.crt;

    # 暗号スイート　↓実際は改行なしで1行
    ssl_ciphers ECDHE-ECDSA-AES256-GCM-SHA384:
    ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES256-GCM-SHA384:
    ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:
    DHE-RSA-AES128-GCM-SHA256;

    # プロトコルバージョン
    ssl_protocols       TLSv1.2;
    # 暗号スイートの順序はサーバが決める
    ssl_prefer_server_ciphers   on;

    location / {
        root   /usr/share/nginx/html;
        index  index.html index.htm;
    }
}
//}

ちなみに暗号スイートとは、「認証はRSAで、鍵交換はECDHE、暗号化アルゴリズムはAESを使う」のように、セキュリティの各パラメータをセットにしたものです。ファーストフード店の「チキンクリームポットパイ＋ポテト＋コーラSのセット」や「オリジナルチキン＋ビスケット＋アイスティーSのセット」みたいなものだと思ってください。どんなセットがあるのか、一覧はIANAのページ@<fn>{iana}で確認できます。

//footnote[iana][Transport Layer Security (TLS) Parameters @<href>{https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml}]

まずはクライアント（ブラウザ）が、希望する暗号スイート群をサーバに送ります。クライアントの希望を受け取ったサーバは、ssl_ciphersディレクティブに書いてある暗号スイートを上から順に探していき、クライアントの希望と共通するものが見つかれば、その暗号スイートを使用します。つまりクライアントが「フィレオフィッシュ＋ポテト＋烏龍茶のセット！なければキッズナゲット＋ビスケット＋烏龍茶のセット！」と希望しても、サーバ側のssl_ciphersディレクティブにそのセットがなければ、接続できずに［クライアントとサーバーで、共通の SSL プロトコル バージョンまたは暗号スイートがサポートされていません。］と表示されてしまうのです。（@<img>{startSSL_123}）

//image[startSSL_123][共通の暗号スイートが見つからず、接続できなかった様子][scale=0.6]{
//}

そのためssl_ciphersディレクティブに、セキュリティを重視して強度の高い暗号スイートだけを書くのか、それとも古い端末との互換性を重視して脆弱な暗号スイートも含めて書くのかは、安全性と対応端末の多さのバランスを考えて決めていくことになります。本来はサイトの運営者が自分で考えて判断すべきことではありますが、次のように設定値の参考を得ることもできます。

 * IPA@<fn>{ipa}が公開している「SSL/TLS暗号設定ガイドライン@<fn>{guide}」では、「高セキュリティ型」「推奨セキュリティ型」「セキュリティ例外型」として3つのssl_ciphersが提示されています。

//footnote[ipa][情報処理推進機構のこと。情報処理技術者試験を実施しているのもIPAです]
//footnote[guide][本書では「高セキュリティ型の設定例（楕円曲線暗号あり）」を使用しています。 @<href>{https://www.ipa.go.jp/security/vuln/ssl_crypt_config.html}]

 * Mozilla@<fn>{mozilla}が提供する「Mozilla SSL Configuration Generator@<fn>{gen}」というサイト（@<img>{mozilla}）を使うと、NGINXとopensslのバージョンを指定して、「Modern」「Intermediate」「Old」を選ぶだけで、適した設定ファイルが出力されます。

//footnote[mozilla][ブラウザのFirefoxを作っているあのMozillaです]
//footnote[gen][@<href>{https://ssl-config.mozilla.org/}]

//image[mozilla][環境や設定を選ぶだけで適した設定ファイルが出力されるMozillaのサイト][scale=0.8]{
//}

設定ファイルが書けたら、構文エラーがないかテストをします。もし書き間違いがあれば、ここでエラーメッセージとして表示されます。

//cmd{
# nginx -t
nginx: the configuration file /etc/nginx/nginx.conf syntax is ok
nginx: configuration file /etc/nginx/nginx.conf test is successful
//}

［test is successful］と表示されたら、NGINXを再起動して設定を反映しましょう。

//cmd{
# systemctl restart nginx.service 
//}

それから、サイトへアクセスしたときに表示される、index.htmlのメッセージも［Let's start SSL/TLS］に変えておきましょう。

//cmd{
# cd /usr/share/nginx/html/
# cp -p index.html index.html.backup
# echo "Let's start SSL/TLS" > index.html
//}

== HTTPSでサイトを開いてみよう

証明書を設置して、NGINXの設定ファイルを修正し、NGINXの再起動もしました。それではブラウザで「@<code>{https://ssl.自分のドメイン名}」を開いてみましょう。鍵マーク付きでHTTPSのページが表示されるはずです。（@<img>{startSSL_114}）

//image[startSSL_114][HTTPSでサイトが表示された！][scale=0.8]{
//}

おめでとうございます！これでサイトをHTTPSにできました！

===[column] 【コラム】ロードバランサでもSSLターミネーションできる

なお本書ではウェブサーバにSSL証明書を設置しましたが、ウェブサーバの手前にロードバランサを置いて、そこにSSL証明書を設置する「SSLターミネーション」という方法もあります。その場合、HTTPSで通信するのは、ユーザのパソコンから終端となるロードバランサーまでで、ロードバランサーとウェブサーバの間はHTTPで通信するのが一般的です。

この方法には、次のようなメリットがあります。

 * 暗号化や復号の処理を行なう終端がロードバランサになるので、ウェブサーバの処理負荷が下がる
 * SSL証明書を設置するのはロードバランサの一箇所だけで済む

今回は取得も設置も手作業で行ないましたが、ウェブサーバが負荷分散のために何十台もあるような環境で、1台1台にSSL証明書とCA証明書を設置@<fn>{license}してNGINXを再起動していくのは大変です。手前のロードバランサでSSLターミネーションするやり方なら、その先にウェブサーバが何台あろうと、SSL証明書を設置するのはロードバランサーの1箇所だけで済みます。

さらにAWSのELB@<fn>{elb}とACM@<fn>{acm}を組み合わせて使うと、今回手作業で行なった秘密鍵とCSRの生成や、SSL証明書と中間CA証明書の設置なども、まるごと任せられます。これは手作業で3時間かけて皮から餃子を作って食べるのと、お店で餃子定食を頼んで食べるのくらい、手間暇に差があるのですが、本書では「餃子を作る工程を一通り体験すること」を目的として、敢えて手作業でSSL証明書を取得しました。

===[/column]

//footnote[license][ちなみに本書で扱ったFujiSSLでは、取得した1枚のSSL証明書を複数台のウェブサーバに設置しても構いません。ですが認証局やSSL証明書によっては、「1台にしか設置できません。2台以上に設置する場合は台数分だけ購入してください」というケースもありますので、購入前にライセンス形態を確認しておきましょう]
//footnote[elb][Elastic Load Balancingの略。AWSのロードバランサ]
//footnote[acm][AWS Certificate Managerの略。SSL証明書の取得や設置、管理をまるごとやってくれるAWSのサービス]
