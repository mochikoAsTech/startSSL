= SSL証明書を取得しよう

HTTPでサイトが見られたので、今度はHTTPSでも見られるよう、必要な材料を「SSL証明書」を入手しましょう。

//pagebreak

== SSL証明書にまつわる登場人物

SSL証明書の取得は、関わってくる登場人物が多いので、最初に登場人物全員が集まる場所として、サーバの中で@<code>{/etc/nginx/}の下に@<code>{ssl}というディレクトリを作っておきます。@<fn>{error}

//footnote[error][もし@<code>{mkdir: cannot create directory ‘/etc/nginx/ssl’: Permission denied}と表示されてしまったら、あなたはいま、うっかり一般ユーザのままでmkdirコマンドを実行しています。コマンドの例で、左側のプロンプトが「#」のときは、rootで実行してください。「sudo su -」と書いてEnterキーを押すとrootになれます]

//cmd{
# mkdir /etc/nginx/ssl/
# cd /etc/nginx/ssl/
//}

== 秘密鍵（startssl.key）を作ろう

先ず最初に作成するのが秘密鍵です。秘密鍵は「.key」や「.pem」@<fn>{pem}という拡張子で作成されることが多いです。秘密鍵は名前のとおり「秘密」にすべきです。つまり、限られた人だけが触れるように管理すべきです。決してメールに添付して送ったり、サーバ内で誰でも見られる@<code>{/tmp/}以下に置いたりしてはいけません。

//footnote[pem][秘密鍵がPEMと呼ばれるテキスト形式で生成されることから、pemという拡張子が使われるようです]

次のopensslコマンドを叩いて、秘密鍵を生成しましょう。左から順に「opensslコマンドで、鍵アルゴリズムがRSAで、鍵の長さは2048ビットで、/etc/nginx/ssl/以下にstartssl.keyというファイル名で秘密鍵を作って」という意味です。

//cmd{
# openssl genrsa 2048 >/etc/nginx/ssl/startssl.key
Generating RSA private key, 2048 bit long modulus
...........................................................................................+++
...........................+++
e is 65537 (0x10001)
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

opensslコマンドで秘密鍵を作るとき、-aes128や-aes256というオプションを付けると、パスフレーズを聞かれて、指定の暗号で暗号化された秘密鍵が出力されます。@<fn>{option}［Enter pass phrase:］や［Verifying - Enter pass phrase:］と表示された際に、いくらキーボードを叩いて入力しても、黒い画面上は何も表示されません。ですが、ちゃんと文字入力はできているので大丈夫です。入力を間違えたらBackspaceキーで消して、書き直すこともできます。

//cmd{
# openssl genrsa -aes128 2048 >/etc/nginx/ssl/with-passphrase.key
Generating RSA private key, 2048 bit long modulus
（中略）
Enter pass phrase:    ←秘密鍵のパスフレーズとして「startssl」と入力
Verifying - Enter pass phrase:    ←もう一度「startssl」と入力
//}

秘密鍵がパスフレーズで保護されていると、秘密鍵を盗んだ誰かが使おうとしても、パスフレーズが分からなければ使えないので安心です。

しかし秘密鍵にパスフレーズが設定されていると、ApacheやNginxといったウェブサーバを再起動した際にも、必ずパスフレーズを聞かれます。もし何かトラブルがあってサーバがOSごと再起動してしまった場合、折角Nginxが自動起動する設定になっていても、パスフレーズを聞くところで止まって起動できず、サイトが自動復旧しない、というトラブルが発生します。

これを回避するには、パスフレーズをファイルに書いておいて、Nginxの自動起動時にそれを読み込むようにする、という方法があります。しかし折角設定したパスフレーズをファイルに書いて同じウェブサーバ内に置いてしまうと、秘密鍵を盗むとき一緒にパスフレーズのファイルも盗まれてしまう可能性が高くなり、もはやパスフレーズを設定した意味がありません。そのため筆者は、ウェブサーバに設置して使う秘密鍵にはパスフレーズは設定しなくてよい、という考えです。

ちなみに、次のように一度パスフレーズありで作った秘密鍵を、パスフレーズなしで複製することも可能です。

//cmd{
# cd /etc/nginx/ssl/
# openssl rsa -in with-passphrase.key -out without-passphrase.key
Enter pass phrase for with-passphrase.key:    ←秘密鍵のパスフレーズ「startssl」を入力
writing RSA key
//}

利便性を保ちつつ安全性も向上させたければ、本番のウェブサーバで使う秘密鍵はパスフレーズなし、バックアップサーバで保管しておく秘密鍵はパスフレーズありにしておく、という方法がいいでしょう。

===[/column]

//footnote[option][さっきは-aes128や-aes256といった「どの暗号で暗号化するか？」のオプションを何も指定しなかったので、パスフレーズは聞かれず、秘密鍵も暗号化されませんでした]

== CSR（startssl.csr）を作ろう

秘密鍵ができたら、続いてCSR（Certificate Signing Request）の作成に進みましょう。CSRは「.csr」という拡張子で作成されることが多いです。CSRは「Certificate Signing Request（証明書署名リクエスト）」という名前のとおり、認証局に対して「こういう内容でSSL証明書を作って署名して」とリクエストする、申請書のようなものです。

左から順に、「opensslコマンドで、CSRを、新しく、秘密鍵はstartssl.keyで、startssl.csrというファイル名で作って」という意味です。

//cmd{
# cd /etc/nginx/ssl/
# openssl req -new -key startssl.key -out startssl.csr
//}

CSRを作成するため、いくつか質問をされます。（@<table>{dn}）@<fn>{ou}

//footnote[ou][本著ではDV証明書を取得するため「組織単位名（OU）」は任意としていますが、証明書の種類や認証局によっては必須のところもあるようです。取得時に認証局のサイトで確認しましょう。DV証明書については後述します]

//table[dn][CSR作成時に聞かれる質問]{
必須/任意	質問	説明	入力する内容
------------------------------------
必須	Country Name	国名（C）	JP
必須	State or Province Name	都道府県名（S/ST）	Tokyo
必須	Locality Name	市町村名（L）	Shinjuku-ku
必須	Organization Name	組織名（O）	mochikoAsTech	
任意	Organizational Unit Name	組織単位名（OU）	入力なし
必須	Common Name	コモンネーム（CN）	ssl.startdns.fun
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

質問に全て答えると、CSRができあがります。「Subject」と書かれた行を見て、生成されたCSRの内容が正しいか確認しましょう。

//cmd{
# openssl req -text -in /etc/nginx/ssl/startssl.csr -noout | head -4
Certificate Request:
    Data:
        Version: 0 (0x0)
        Subject: C=JP, ST=Tokyo, L=Shinjuku-ku, O=mochikoAsTech, CN=ssl.startdns.fun
//}

CSRをcatコマンドで表示して、「-----BEGIN CERTIFICATE REQUEST-----」から「-----END CERTIFICATE REQUEST-----」までをメモしておきましょう。メモしたCSRはこの後使用します。

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

=== 【ドリル】CSRで入力すべきなのはクライアントの情報？

==== 問題

A銀行のウェブサイトをHTTPSで作ることになりました。SSL証明書@<fn>{evSsl}の取得はA銀行の代わりに広告代理店のB社が行い、さらにサイトの制作や運用はA銀行からWeb制作会社のC社に委託する場合、CSRで入力する住所や会社名はA銀行・B社・C社のどれにすべきでしょうか？

 * A. A銀行のウェブサイトなんだからA銀行を入力すべき
 * B. A銀行から任されてSSL証明書を買うのはB社だからB社を入力すべき
 * C. 実際にサイトの管理を任されているのはC社だからC社を入力すべき

//footnote[evSsl][SSL証明書の種類は「EV証明書」とします。EV証明書については後述します]

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。ウェブサイトの運営元がA銀行であることを証明するためのSSL証明書なので、CSRではA銀行（クライアント）の情報を記載すべきです。

A銀行のフィッシングサイトが出てきたときに、エンドユーザが「本物のサイトか確認しよう」と思って証明書の情報を見て、B社やC社の情報が表示されたら「A銀行じゃない！」となってしまいます。

== SSL証明書の取得申請を出そう

［FujiSSL］で検索して、［FujiSSL-安心・安全の純国産格安SSLサーバ証明書］をクリック（@<img>{startSSL_86}）します。

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

クーポンコードは［使用しない］、申し込み種別は［新規申し込み］、商品選択は［ドメイン認証］の［FujiSSL］になっていることを確認（@<img>{startSSL_90}）します。

//image[startSSL_90][クーポンコード、申し込み種別、商品選択を確認][scale=0.8]{
//}

下へスクロールして、お申込み年数が［FujiSSL 1年 1,100円］@<fn>{price}になっていることを確認（@<img>{startSSL_91}）したら、CSRに、先ほど「-----BEGIN CERTIFICATE REQUEST-----」から「-----END CERTIFICATE REQUEST-----」までをメモしておいたCSRをペーストします。

//footnote[price][2019年2月現在、FujiSSLの「ドメイン認証シングルタイプ」というSSL証明書は、有効期間1年で税込1,100円です]

//image[startSSL_91][CSRをペーストする][scale=0.8]{
//}

［次へ］をクリック（@<img>{startSSL_92}）してください。

//image[startSSL_92][［次へ］をクリック][scale=0.8]{
//}

認証方式は［DNS認証］を選択（@<img>{startSSL_93}）してください。これは「CSRのコモンネームで指定したドメイン名が、あなたの持ち物であることをどうやって証明しますか？」ということを聞かれています。対象のドメイン名で、メールを受信してURLを踏むか、指定された内容のリソースレコードをDNSで追加するか、サイトに指定された内容のファイルをアップするか、いずれかの方法で「このドメイン名（筆者ならssl.startdns.fun）は私の持ち物です」ということを証明しなければいけません。

今回はDNSでTXTレコードを追加する、という方法で証明するので、［DNS認証］を選択して［次へ］をクリックします。

//image[startSSL_93][［DNS認証］を選択して［次へ］をクリック][scale=0.8]{
//}

今回購入するのはDV証明書です。DV証明書は「そのドメイン名の使用権があること」だけを証明してくれます。サイトの運営者が日本にいることや、東京の新宿区にオフィスがあること、mochikoAsTechという組織であることなどは確認も証明もしないので、実際の証明書にもそれらの情報は反映されません。（@<img>{startSSL_94}）

//image[startSSL_94][［申請情報入力］画面][scale=0.8]{
//}

［申請組織担当者情報］と［技術担当者情報］を英語表記で入力（@<img>{startSSL_95}）します。ここで入力した住所や電話番号、個人名などは外向けに公開されることはありませんので、安心して入力してください。@<fn>{evOrOv}この後、ここで入力した［Eメールアドレス］宛てに、SSL証明書が送られてきます。メールアドレスを間違えないよう注意してください。すべて入力したら、［次へ］をクリック（@<img>{startSSL_96}）します。

//footnote[evOrOv][EV証明書やOV証明書の場合は、ここで入力した担当者宛てに実在確認の連絡が入ります。詳細については後述します]

//image[startSSL_95][［申請組織担当者情報］と［技術担当者情報］を入力][scale=0.8]{
//}

//image[startSSL_96][［次へ］をクリック][scale=0.8]{
//}

［決済情報入力］に、SSL証明書代を支払うクレジットカード情報を入力（@<img>{startSSL_97}）します。

//image[startSSL_97][クレジットカード情報を入力][scale=0.8]{
//}

［書類送付先］で［請求書宛名］、［納品書宛名］、［領収書宛名］を記入したら、［上記の内容で注文を確定する］をクリック（@<img>{startSSL_98}）します。

//image[startSSL_98][［上記の内容で注文を確定する］をクリック][scale=0.8]{
//}

「注文を確定します。よろしいですか？」と表示（@<img>{startSSL_99}）されたら、［OK］をクリックします。

//image[startSSL_99][［OK］をクリック][scale=0.8]{
//}

「この内容で決済を確定します。よろしいですか？」と表示（@<img>{startSSL_100}）されます。「1年間有効なSSL証明書を1,100円で買うんだ！」というケツイ@<fn>{ketsui}をしたら、［OK］をクリックします。

//image[startSSL_100][1,100円払うケツイをして［OK］をクリック][scale=0.8]{
//}

//footnote[ketsui][UNDERTALEというゲームでは「ケツイを　ちからに　かえるんだ…！」という台詞が繰り返し出てきます]

お申し込み完了のページが表示（@<img>{startSSL_101}）されました。先ほど登録したメールアドレス宛に、DNS設定情報を知らせるメールが届いていますので確認しましょう。

//image[startSSL_101][［お申込み完了］画面][scale=0.8]{
//}

== DNSの設定をしよう

［CommonName=ssl.自分のドメイン名］から始まる件名のメール（@<img>{startSSL_102}）がすぐに届きました。「CSRのコモンネームで指定したドメイン名がssl.startdns.funの場合、startdns.funのTXTレコードを追加して、メールに書いてある値を設定するよう書いてあります。

//image[startSSL_102][追加すべきTXTレコードの値がメールで届いた][scale=0.8]{
//}

例えばネームサーバが「お名前.com」なら、DNS設定の画面でこのようにTXTレコードを追加（@<img>{startSSL_103}）します。今回はサブドメインを含まないドメイン名を追加するので、［ホスト名］には何も入力しません。［VALUE］には、メールに書いてあった値をそのままコピーペーストします。

//image[startSSL_103][「自分のドメイン名」のTXTレコードを追加する][scale=0.6]{
//}

TXTレコードができたかどうかは、次のdigコマンドで確認できます。digコマンドをたたいた結果、サーバのIPアドレスが返ってくればAレコードは設定できています。

//cmd{
$ dig 自分のドメイン名 txt +short
//}

筆者の場合は、次のように表示されました。

//cmd{
$ dig startdns.fun txt +short
"20200204005703EA923DBFD370D3A4C260E09747A37082277DDD5B966ED7C2BB87C0386B17A076"
//}

TXTレコードを追加してから、おおよそ30分後にSSL証明書がメール（@<img>{startSSL_104}）で届きました。

//image[startSSL_104][SSL証明書がメールで届いた][scale=0.8]{
//}

メールに添付されているZIPファイル（ssl.自分のドメイン名.zip）にSSL証明書が入っていますのでダウンロードします。（@<img>{startSSL_105}）

//image[startSSL_105][メールに添付されているZIPファイル][scale=0.4]{
//}

Windowsの方もMacの方も、ダウンロードしたZIPファイルはデスクトップに置いてください。（@<img>{startSSL_106}）

//image[startSSL_106][ダウンロードしたZIPファイルはデスクトップに置く][scale=0.4]{
//}

ZIPファイルを右クリックして、［すべて展開］をクリックします。（@<img>{startSSL_107}）

//image[startSSL_107][右クリックして［すべて展開］をクリック][scale=0.4]{
//}

［展開］をクリックします。（@<img>{startSSL_108}）

//image[startSSL_108][［展開］をクリック][scale=0.6]{
//}

展開したフォルダ（@<img>{startSSL_109}）の中の［server.crt］がSSL証明書で、［ca-bundle.ca］が中間CA証明書です。READMEはファイルの説明書です。

//image[startSSL_109][erver.crtがSSL証明書で、ca-bundle.caが中間CA証明書][scale=0.6]{
//}

どちらも必要なものなので、この2つのファイルをサーバにアップロードしましょう。

== SSL証明書をサーバに設置しよう

それではSSL証明書をサーバに設置します。NGINXではSSL証明書と中間CA証明書の2つを、1ファイルにまとめて使用するので、まずはアップロードして、それから1ファイルにまとめる作業を行ないます。

=== Windowsで証明書と中間CA証明書をアップしよう

Windowsのパソコンを使っている方は、RLoginを起動します。［startSSLInstance］を選択して、［OK］をクリック（@<img>{startSSL_110}）します。

//image[startSSL_110][RLoginを起動して［startSSLInstance］を選択してログイン][scale=0.6]{
//}

黒い画面が開いたら、［ファイル］から［SFTPファイルの転送］をクリック（@<img>{startSSL_111}）します。

//image[startSSL_111][［ファイル］から［SFTPファイルの転送］をクリック][scale=0.6]{
//}

左側があなたのパソコンで、右側がサーバです。左側をデスクトップに展開したフォルダ@<fn>{folder}にしたら、［server.crt］と［ca-bundle.ca］を右側にドラッグ＆ドロップ（@<img>{startSSL_112}）してください。これでサーバの「/home/opc」にファイルがアップロードされます。

//footnote[folder][筆者の場合は「C:\Users\mochikoAsTech\Desktop\ssl.startdns.fun」でした]

//image[startSSL_112][［ファイル］から［SFTPファイルの転送］をクリック][scale=0.6]{
//}

右側に［server.crt］と［ca-bundle.ca］がアップされたら、×を押してファイル転送の画面は閉じて構いません。（@<img>{startSSL_113}）

//image[startSSL_113][［ファイル］から［SFTPファイルの転送］をクリック][scale=0.6]{
//}

=== Macで証明書と中間CA証明書をアップしよう

Macを使っている方は、ターミナルを起動してください。scpコマンドを使って、Macの中にある［server.crt］と［ca-bundle.ca］を、サーバにアップロードします。［展開したフォルダ］と［パブリックIPアドレス］の部分は、ご自身のものに書き換えてください。

//cmd{
$ cd ~/Desktop/展開したフォルダ
$ scp -i ~/Desktop/startSSLKey server.crt ca-bundle.ca opc@パブリックIPアドレス:/home/opc/
server.crt    100%  0   0.0KB/s   00:00    
ca-bundle.ca  100%  0   0.0KB/s   00:00   
//}

=== SSL証明書と中間CA証明書を1ファイルにまとめよう

サーバにログインしている状態で、次のコマンドを叩いて、先ほどアップロードした［server.crt］と［ca-bundle.ca］が、ちゃんと「/home/opc/」以下に存在していることを確認します。

//cmd{
$ sudo su -

# ls /home/opc/
ca-bundle.ca  ssl.startdns.fun.crt
//}

続いて2つのファイルから、新たに［startssl.crt］というファイルを作りましょう。@<fn>{awk}NGINXではSSL証明書と中間CA証明書という2つのファイルを、1つのファイルにがっちゃんこ！とつなげて使うためです。

//cmd{
# cd /etc/nginx/ssl/
# awk 1 /home/opc/ssl.startdns.fun.crt /home/opc/ca-bundle.ca > startssl.crt
//}

//footnote[awk][このときcatコマンドで結合すると、SSL証明書と中間CA証明書の間に改行が入らず、「-----END CERTIFICATE----------BEGIN CERTIFICATE-----」のようになってしまうため、awkコマンドを使っています]

catコマンドで［startssl.crt］を確認してみましょう。次のように「-----BEGIN CERTIFICATE-----」と「-----END CERTIFICATE-----」が、繰り返し3つ表示されれば大丈夫です。

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

これでファイルの準備は完了です。

== NGINXでHTTPSのバーチャルホストを作ろう

「/etc/nginx/conf.d/」というディレクトリの下で、もともとあった設定ファイルをバックアップしておきます。

//cmd{
# cd /etc/nginx/conf.d/
# mv default.conf default.conf.backup
//}

viコマンドで、同じ場所に新しい設定ファイルを作ります。viコマンドでファイルを編集するときは、i（アイ）を押してから入力します。書き終わったらESCキーを押して、「:wq」と入力してEnterキーを押せば変更が保存されます。

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
    # SSL証明書
    ssl_certificate     /etc/nginx/ssl/startssl.crt;

    # 暗号スイート
    ssl_ciphers ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES128-GCM-SHA256;
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

それからアクセスしたときに表示される、index.htmlの文字も［Let's start SSL/TLS］に変えておきましょう。

//cmd{
# cd /usr/share/nginx/html/
# cp -p index.html index.html.backup
# echo "Let's start SSL/TLS" > index.html
//}

== HTTPSでサイトを開いてみよう

証明書を設置して、NGINXの設定ファイルを修正し、NGINXの再起動もしたのでブラウザで「http://ssl.自分のドメイン名」を開いてみましょう。鍵マーク付きでHTTPSのページが表示されるはずです。（@<img>{startSSL_114}）

//image[startSSL_114][HTTPSでサイトが表示された！][scale=0.8]{
//}

===[column] 【コラム】ロードバランサーでSSLターミネーションする方法もある

なお本著ではウェブサーバにSSL証明書を設置しましたが、ウェブサーバの手前にロードバランサを置いて、そこにSSL証明書を設置して、SSLターミネーションを行う方法もあります。その場合、SSLで通信するのはエンドユーザのパソコンから終端となるロードバランサーまでで、ロードバランサーとウェブサーバの間はHTTPで通信するのが一般的です。

この方法には、次のようなメリットがあります。

- 暗号化や復号の処理を行う終端がロードバランサになるので、ウェブサーバの処理負荷が下がる
- （AWSのELBとACMの場合は）証明書の取得や更新、設置が自動で行われる

===[/column]
