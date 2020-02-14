= SSL/TLSの仕組み

SSL証明書を取得して、実際にHTTPSのサイトを公開できました。

実践したことと照らし合わせながら、SSL/TLSの仕組みを学んでいきましょう。

//pagebreak

== SSL証明書とは

サイトをHTTPS化するためにSSL証明書を取得しました。でもSSL証明書とは、結局のところ何で、どういう働きをしているのでしょう？

=== SSLサーバ証明書とSSLクライアント証明書

皆さんがさっき取得、設置した「SSL証明書」ですが、実はSSLサーバ証明書とSSLクライアント証明書の2種類（@<img>{sslClientCert}）があります。ざっくり言うとサーバの身元を証明するのがSSLサーバ証明書で、クライアントの身元を証明するのがSSLクライアント証明書です。

//image[sslClientCert][SSLサーバ証明書とSSLクライアント証明書][scale=0.8]{
//}

単に「SSL証明書」という略称で呼んだ場合は、「SSLサーバ証明書」のことを指すことがほとんどです。本書でもSSLサーバ証明書のことを指して、SSL証明書という言葉を使用しています。

=== SSL証明書はどんなときに使われている？

SSL証明書はどんなときに使われているのでしょうか？SSL証明書は、あなたがブラウザで「https://」から始まるURLのサイトを開いて、次のようなマーク（@<img>{startSSL_81}、@<img>{startSSL_82}）が表示されているときに使われています。

//image[startSSL_81][ChromeでHTTPSのサイトを開いたとき][scale=0.6]{
//}

//image[startSSL_82][FirefoxでHTTPSのサイトを開いたとき][scale=0.6]{
//}

逆に「http://」から始まるURLのサイトを開いて、次のようなマーク（@<img>{startSSL_80}、@<img>{startSSL_79}）が表示されているときは使われていません。

//image[startSSL_80][ChromeでHTTPのサイトを開いたとき][scale=0.6]{
//}

//image[startSSL_79][FirefoxでHTTPのサイトを開いたとき][scale=0.6]{
//}

== SSL証明書は異なる3つの仕事をしている

「SSL証明書は@<code>{https://}から始まるページで使われている」ということが分かりました。では@<code>{https://}から始まるページにおいて、SSL証明書は一体何をしているのでしょうか。

実は、SSL証明書は異なる3つの仕事をしています。たとえば、あなたが銀行振込をするためにイグザンプル銀行のウェブサイト（https://bank.example.com/）に接続したとき、SSL証明書は次のような3つの仕事をします。

 * なりすましを防ぐ
 ** 「bank.example.comさん、ページを見せて」というリクエストに対して、レスポンスでページを返してきたのが、本当にbank.example.comであることを認証する
 * データの改ざんを防ぐ
 ** イグザンプル銀行のウェブサイトで入力した振込先の情報が、サーバに届くまでに他の振込先に書き換えられていないことを確認する
 ** リクエストに対して返ってきた残高のページが、クライアントまでの途中経路で改ざんされていないことを確認する
 * 情報の漏洩を防ぐ
 ** サーバへ送信したIDやパスワード、振込先の情報などが第三者に見られないよう暗号化して保護する
 ** 入出金の明細がサーバからクライアントへ届くまでの間に、第三者に見られないよう暗号化して保護する

厳密には、3つめの暗号化はSSL証明書そのものの働きではありません。暗号化に必要な鍵交換を行なう過程でSSL証明書が仕事をしています。

=== HTTPSの実際の流れ

ではHTTPSの全体を流れを掴むため、あなたが作ったサイト（https://ssl.自分のドメイン名/）をブラウザで開いたときのやりとりを、ざっくりと追いかけてみましょう。あなたのブラウザが「クライアント」で、Oracle Cloud上で立てたHTTPSのサイトが動いているのが「サーバ」です。

==== 認証を行なう

先にRSA@<fn>{rsa}による認証を行ないます。

//footnote[rsa][もともとは認証だけでなく鍵交換もRSAで行なわれていましたが、RSAによる鍵交換は、一度秘密鍵が盗まれてしまうと、過去のやりとりもさかのぼって全ての暗号データを復号可能という問題がありました。そのためTLS1.3ではRSA鍵交換は廃止されています]

1. ブラウザでHTTPSのサイト（https://ssl.自分のドメイン名/）を開く

2. クライアントからOracle Cloudのウェブサーバへリクエストを投げる

3. サーバがリクエストを受け取る

4. サーバ内にあるFujiSSLのSSL証明書をレスポンスで返す

 * この「SSL証明書」は次の2つを指す
 ** SSL証明書本体（公開鍵を含む）
 ** 認証局による署名（SSL証明書本体のハッシュ値を認証局の秘密鍵で暗号化@<fn>{angouka}したもの）

5. クライアント側でSSL証明書を受け取って次の5つを行なう

6. ブラウザのトラストアンカー（信頼する証明書）に含まれている認証局によって発行されたSSL証明書なのか確認

 * これで渡されたSSL証明書を信頼してよいことが分かる

7. 認証局による署名を、ブラウザのトラストアンカー（信頼する証明書）に含まれる公開鍵で復号して、証明書本体のハッシュ値を取り出す

8. ハッシュ関数でSSL証明書本体のハッシュ値を出力

9. 取り出したハッシュ値と、自分で出力したハッシュ値を突き合わせて同一であることを確認する

 * これで渡されたSSL証明書本体が改ざんされていないことが分かる

10. SSL証明書本体の@<fn>{san}に記載されているFQDN@<fn>{fqdn}と、リクエスト先のFQDN（bank.example.com）が同一であることを確認

 * これでレスポンスを返してきた相手がなりすましでないことが分かる

//footnote[angouka][ここは実態としては「秘密鍵で復号」らしいのですが、まだ暗号化していないものを復号するイメージを筆者はうまく理解できなかったので、解説はこちらを参照ください。 「電子署名=『秘密鍵で暗号化』」という良くある誤解の話 - Qiita @<href>{https://qiita.com/angel_p_57/items/d7ffb9ec13b4dde3357d}]
//footnote[san][Subject Alternative Nameの略。どのドメイン名に対するSSL証明書なのか、対象のドメイン名が書いてあるフィールド]
//footnote[fqdn][FQDNはFully Qualified Domain Nameの略で、日本語だと完全修飾ドメイン名。example.co.jpというドメイン名があったとき、個々のexampleやcoやjpやexample.coなどは相対ドメイン名で、example.co.jpがFQDNです]

==== DH鍵交換による暗号化通信を行なう

認証が終わると、続けてDH鍵交換@<fn>{dh}を行ないます。

//footnote[dh][Diffie-Hellman鍵交換]

1. サーバはDH公開鍵交換のために使い捨ての鍵ペア（秘密鍵・公開鍵）を作る

 * この鍵ペアは、SSL証明書を取得するときに作った鍵ペア（秘密鍵・公開鍵）とはまた別物
 * 以後この鍵ペアを「サーバのDH用の秘密鍵・公開鍵」と呼ぶ

2. クライアントもDH公開鍵交換のために使い捨ての鍵ペア（秘密鍵・公開鍵）を作る

 * 以後この鍵ペアを「クライアントのDH用の秘密鍵・公開鍵」と呼ぶ

3. サーバはSSL証明書用の秘密鍵で、サーバのDH用の公開鍵を暗号化してクライアント側に渡す

4. クライアントは「認証」で受け取ったSSL証明書本体に含まれていた「SSL証明書用の公開鍵」で、サーバのDH用の公開鍵を復号する

5. クライアントは自分が作ったDH用の公開鍵を、サーバのDH用の公開鍵で暗号化してサーバに送る

6. サーバは、受け取ったクライアントのDH用の公開鍵を、サーバのDH用の秘密鍵で復号する

7. これでクライアントとサーバはお互いに相手のDH用の公開鍵を持っている状態になる

 * サーバのDH用の公開鍵と、クライアントのDH用の公開鍵のセットを、共通鍵の素（プリマスターシークレット）と呼ぶ

8. クライアントサーバは、それぞれプリマスターシークレットを素にして共通鍵を作る

9. 以降、同一セッションの間は、双方この共通鍵で暗号化および復号してデータをやりとりする

このようにRSAによる認証と、DH鍵交換の組み合わせで、HTTPSの暗号化通信が行なわれています。

=== 正当性を証明する中間CA証明書

ではここで、サイバートラストが提供する「SSL証明書の設定確認ツール」@<fn>{cybertrust}を使って、あなたが作ったサイトのSSL証明書を確認（@<img>{cybertrust01}）してみましょう。［FQDN1］に［ssl.自分のドメイン名］を入力し、［設定を確認する］をクリックします。

//footnote[cybertrust][@<href>{https://sstool.cybertrust.ne.jp/support_tool/index01.php}]

//image[cybertrust01][［ssl.自分のドメイン名］を入力して［設定を確認する］をクリック][scale=0.6]{
//}

すると［証明書は正しく設定されています。］というメッセージと共に、証明書の階層が表示（@<img>{cybertrust02}）されました。

//image[cybertrust02][証明書の階層が表示された][scale=0.5]{
//}

［中間CA証明書1］と［中間CA証明書2］で、それぞれ［詳細情報を表示する］をクリックすると、詳細が表示されます。いろいろなことが記載されていますが、要約すれば次の表に挙げたことが書かれています。

 * SSLサーバ証明書
 ** ［ssl.startdns.fun］というサイトの運営者が、確かにそのドメイン名を管轄していることを、［SECOM Trust Systems CO.,LTD.］が証明する
 * 中間CA証明書1
 ** SSLサーバ証明書を発行した［SECOM Trust Systems CO.,LTD.］が正当な認証局であることを、［Security Communication RootCA2］が証明する
 * 中間CA証明書2
 ** 中間CA証明書1を発行した［Security Communication RootCA2］が正当な認証局であることを、［Security Communication RootCA1］が証明する

信頼の連鎖ですね。［ssl.startdns.fun］というサイトの運営者を仮にAさんとすると、Aさんがドメイン名の持ち主であることをBさんが、Bさんの正当性をCさんが、Cさんの正当性をDさんが証明しています。

SSL証明書と中間CA証明書1、2は［startssl.crt］というファイル名でサーバに設置されており、HTTPSでサイトを開いたときにサーバからクライアント（ブラウザ）へ渡されました。ですがあなたは身も知らないDさんこと［Security Communication RootCA1］を信頼できますか？Dさんの正当性はいったい誰が証明するのでしょう？

=== ルート証明書はトラストストアにある

実は、中間CA証明書2を発行したDさんこと［Security Communication RootCA1］の正当性を証明する「ルート証明書」は、皆さんが使っているブラウザに最初から入っています。Chromeで［設定］を開いたら［証明書］で検索（@<img>{startSSL_116}）して、［証明書の管理］をクリックします。

//image[startSSL_116][［証明書の管理］をクリック][scale=0.6]{
//}

［信頼されたルート認証機関］のタブをクリック（@<img>{startSSL_117}）すると、そこにDさんこと［Security Communication RootCA1］の正当性を証明する「ルート証明書」がありました。ちなみにルート証明書の［発行先］と［発行者］を見ると、どちらも同じ［Security Communication RootCA1］になっています。これはDさんの正当性はDさん自身が証明し、ブラウザがDさんのルート証明書を「信頼できるルート証明書である」と判断して格納場所（ルートトラストストア）に入れているので、信頼の連鎖が繋がった、ということです。

//image[startSSL_117][［信頼されたルート認証機関］にルート証明書があった][scale=0.6]{
//}

このようにSSL証明書と中間CA証明書がウェブサーバにあり、信頼の起点となるルート証明書がブラウザにあることで、SSL証明書は成り立っています。SSL証明書ってこんな仕組みになっていたんですね。

=== ウェブページは1往復で表示されるわけじゃない

ところで1つのウェブページを表示するとき、クライアント（あなたのブラウザ）とサーバのやりとりは、「トップページをください」「はい完成品をどうぞ」の一往復だけではありません。次のように、何往復ものリクエストとレスポンスでパーツを揃えていってページが表示されます。

 * 「techbookfest.orgさん、tbf08のページをください」「はい、HTMLをどうぞ」
 * 「techbookfest.orgさん、main.jsをください」「はい、main.jsをどうぞ」
 * 「techbookfest.orgさん、styles.cssをください」「はい、styles.cssをどうぞ」
 * 「techbookfest.orgさん、top.jpgをください」「はい、top.jpgをどうぞ」

Chromeのメニューから［その他のツール］の［デベロッパーツール］を開いて、［Network］タブを選択した状態で、たとえば技術書典8のサイト@<fn>{tbf08}を開くと、次のようにたくさんの行が表示（@<img>{startSSL_115}）されます。2019年2月時点、このページは54往復のリクエストとレスポンスで表示されており、この1行1行が「○○をください」「はい、どうぞ」という、リクエストとレスポンスの往復を表しているのです。

//footnote[tbf08][@<href>{https://techbookfest.org/event/tbf08}]

//image[startSSL_115][54往復のリクエストとレスポンスで表示された技術書典8のページ][scale=0.8]{
//}

=== HTTPの混在コンテンツはブロックされてしまう

「HTTPSから始まるURLを開いたときに、鍵マークではなくiマークが表示される」という現象には、この「ページの表示は一往復じゃない」という部分が大きく関係しています。

通常、ブラウザで@<code>{https://}から始まるURLを開くと、前述のとおり、リクエストしたページはHTTPSで暗号化された状態で届きます。しかし取得したページのHTMLで、「<img src="http://www.example.com/images/top.png">」のように、絶対パスで画像を指定する<img>タグが含まれていた場合、その画像ファイルは暗号化されていないHTTPで送られてきます。（@<img>{mixedContents}）

//image[mixedContents][混在コンテンツ（mixed content）はエラーが出る][scale=0.6]{
//}

つまり、せっかくウェブページをHTTPSにしても、そのウェブページのHTMLの中で、CSSや画像ファイルのURLを@<code>{http://}から始まる形式にしていたり、YouTubeなどのコンテンツを@<code>{http://}から始まる形式で埋め込んでいると、ページが表示されるまでのたくさんの往復の中で、一部がHTTPになってしまっているので、ブラウザが鍵マークの代わりにiマークを表示して、［このサイトへの接続は完全には保護されていません］と警告（@<img>{mixedContents02}）を出すのです。

//image[mixedContents02][［このサイトへの接続は完全には保護されていません］と警告が出る][scale=0.4]{
//}

この問題は混在コンテンツ（mixed content）と呼ばれています。2020年3月にリリース予定のChromeのバージョン81@<fn>{schedule}からは、この混在コンテンツが存在した場合、対象のプロトコルがHTTPからHTTPSへ自動的に変更され、さらにHTTPSでの読み込みに失敗すると、そのリソース（@<code>{http://}で始まる形式にしていたCSSや画像、埋め込みコンテンツ）がブロックされる変更が予定されています。

//footnote[schedule][@<href>{https://developers-jp.googleblog.com/2019/11/https.html}, @<href>{https://security.googleblog.com/2020/02/protecting-users-from-insecure_6.html}]

混在コンテンツを直すには、たとえば@<code>{<img src="http://www.example.com/images/top.png">}のようになっていた<img>タグを「<img src="/images/top.png">」のようにパスの部分だけにします。これならページをHTTPで開いたときは画像もHTTPで、ページをHTTPSで開いたときは画像もHTTPSで表示されるため、混在コンテンツにはなりません。

あるいは「画像はページとは別のドメイン名なので、パスだけでなくドメイン名から指定しなければいけない」という場合は、<img>タグを@<code>{<img src="//image.example.com/images/top.png">}のようにプロトコルを省略して書くことで、先ほどと同じように、ページをHTTPで開いたときは画像もHTTPで、ページをHTTPSで開いたときは画像もHTTPSで表示されます。このようにして混在コンテンツを解消してやれば、きちんと鍵マークが表示されるようになります。

ちなみに「Google HTML/CSS Style Guide@<fn>{guide}」では、このプロトコルを省略する書き方は非推奨とされています。ページがHTTPかHTTPSかに関わらず、画像はHTTPSで表示して構わない、という場合は、@<code>{<img src="https://www.example.com/images/top.png">}のように指定するのがいいでしょう。

//footnote[guide][@<href>{https://google.github.io/styleguide/htmlcssguide.html#Protocol}]

=== 〈トラブル〉SSL証明書の有効期限がうっかり切れてしまった

2020年2月、マイクロソフトが提供するチャットサービス、「Microsoft Teams」が一時的に使えなくなる障害が発生@<fn>{teams}しました。SSL証明書には1年もしくは2年の有効期限があります。有効期限が切れる前に更新を行なって、新しいSSL証明書に差し替えなければいけないのですが、この更新を怠って有効期限が切れてしまったことで障害が発生したようです。

このようにSSL証明書の更新を忘れて、有効期限がうっかり切れてしまうトラブルは昔から後を絶ちません。たとえば株式会社はてなが提供しているサーバ監視サービスのMackerelでは、URL外形監視で、SSL証明書の残り日数が閾値を超えるとアラートが発報@<fn>{mackerel}されます。カレンダーに更新予定を入れて管理するのもひとつの対策ですが、こうした方法でSSL証明書の有効期限を監視する方法がより確実です。

//footnote[teams][@<href>{https://twitter.com/MSFT365Status/status/1224351597624537088}]
//footnote[mackerel][URL外形監視にてSSL証明書の有効期限を監視できるようになりました - Mackerel ブログ @<href>{https://mackerel.io/ja/blog/entry/2016/01/29/115632}]

== SSL証明書はどうしてあんなに値段に差があるの？

SSL証明書の仕組みが分かったところで、SSL証明書のあるあるな疑問、「どうしてSSL証明書はあんなに値段に差があるの？」について少しお話ししておきましょう。

SSL証明書で検索してみると、DigiCert&Symantecは219,000円、GMOグローバルサインは59,800円、そして本書で買ったFujiSSLは1,000円でした。@<fn>{price}

//footnote[price][いずれも2020年2月時点、有効期間1年の税抜金額です]

なぜこんなに価格差があるのでしょうか。DigiCert&Symantecは知名度が金額に反映されているので高いのでしょうか？FujiSSLはあまりにも格安ですが、同じ「SSL証明書」という名前でも中身が何か違うのでしょうか？

=== 同じ「SSL証明書」でも3つの種類がある

実は同じ「SSL証明書」という名前で呼ばれていても、その実態は3種類に分かれています。分かりやすくいうと「高い」「普通」「安い」の3種類で、それぞれ「EV証明書」「OV証明書」「DV証明書」という名前です。

 * DV証明書（Domain Validation）
 ** サイトの運営者がそのドメイン名の持ち主であることを証明してくれる。個人でも取得できる。
 ** 当該ドメイン名でメールを受信してURLを踏んだり、TXTレコードを設定したり、サイトに指定のファイルをアップすることで認証される
 ** 商品例：FujiSSL、RapidSSL、Let's Encrypt（無料）

 * OV証明書（Organization Validation）
 ** サイトを運営する組織が実在することと、本物の組織であることを証明してくれる。個人では取得できない。
 ** サイト運営者の実在をメールと電話で確認することで認証される
 ** 商品例：企業認証SSL（GMOグローバルサイン）、セキュア・サーバID（DigiCert&Symantec）

 * EV証明書（Extended Validation）
 ** サイトを運営する法人組織が実在することと、本物の組織であることを証明してくれる。個人や法人格のない組織では取得できない。
 ** サイトを運営する法人組織の実在をより厳格に書類と電話で確認することで認証される
 ** 商品例：SureServer EV（サイバートラスト）、セキュア・サーバ ID EV（DigiCert&Symantec）

DV証明書（@<img>{startSSL_119}）とEV証明書（@<img>{startSSL_118}）のサイトを比較すると、値段も取得の煩雑さもEV証明書の方が圧倒的に上ですが、残念ながらアドレスバーを見ただけでは何の差もありません。

//image[startSSL_119][本書で作ったサイトのDV証明書の鍵マーク][scale=0.6]{
//}

//image[startSSL_118][三井住友銀行のEV証明書の鍵マーク][scale=0.6]{
//}

=== さよならグリーンバー

以前はEV証明書であれば、どのブラウザでも次のようにグリーンバーでサイトの運営法人が表示（@<img>{startSSL_122}）され、一目で本物のサイトと判別ができました。

//image[startSSL_122][以前はどのブラウザでもグリーンバーが表示されていた][scale=0.4]{
//}

//footnote[greenBar][画像は@<href>{https://www.cybertrust.ne.jp/sureserver/lp/ev.html}より引用]

ですが2019年9月にリリースされたChromeバージョン77、そして同年10月にリリースされたFirefoxバージョン70からは、EV証明書であってもグリーンバーが表示されなくなりました。2020年2月現在、誰でも安価に取得できるDV証明書と、厳格に実在確認をするEV証明書のどちらも、URLの左側にでる鍵マークは同一で、ぱっと見では区別がつかなくなっています。さらに鍵マークをクリックすると、どちらも緑色で［この接続は保護されています］と表示されます。EV証明書だと運営組織名も表示（@<img>{startSSL_121}）されますが、これをEV証明書の恩恵と見なして高い金額を払うのはつらいだろうな、というのが筆者の印象です。

//image[startSSL_120][DV証明書でも緑色で［この接続は保護されています］と表示される][scale=0.4]{
//}

//image[startSSL_121][EV証明書だと運営組織名も表示される][scale=0.4]{
//}

=== 任意のサブドメインで使えるワイルドカード証明書

SSL証明書には、「*.example.com」のように任意のサブドメインで使えるワイルドカード証明書という種類があります。本番環境、ステージング環境、テスト環境などで1つの証明書を共用できるので便利です。

このときSSL証明書のSANが「*.example.com」のみだった場合、元となるドメインや、サブドメインのサブドメインには使用できないので注意が必要です。

 * SANが「*.example.com」のワイルドカード証明書が使えるドメイン名
 ** www.example.com
 ** prod.example.com
 ** stg.example.com
 ** test.example.com
 * SANが「*.example.com」のワイルドカード証明書が使えないドメイン名
 ** old.www.example.com
 ** example.com

認証局によっては「*.example.com」や「www.example.com」のSSL証明書を買うと、SANに「example.com」を無料サービス@<fn>{service}してくれるところもあります。なおEV証明書のワイルドカード証明書は存在しません。

//footnote[service][たとえば「FujiSSL ワイルドカード」は「*.example.com」で申し込むと、SANに「example.com」を自動付加してくれます]

=== 【ドリル】リダイレクトするだけでもwwwなしの証明書は必要？

==== 問題

次のようなリダイレクトの設定を行なったとします。

 1. http://example.com/ へのアクセスは4にリダイレクト
 1. http://www.example.com/ へのアクセスは4にリダイレクト
 1. https://example.com/ へのアクセスは4にリダイレクト
 1. https://www.example.com/ でサイトを表示

このとき用意すべきなのは、どのドメイン名のSSL証明書でしょうか？

 * A. www.example.comのSSL証明書
 * B. example.comのSSL証明書
 * C. example.comとwww.example.comのSSL証明書

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はCです。「リダイレクトする」というレスポンスを返す処理よりも前に、認証や鍵交換が行なわれますので、3のためにexample.comのSSL証明書も必要です。

=== 〈トラブル〉サイトをHTTPS化したら古い端末で別サイトが表示された

1台のウェブサーバで複数のサイトが同居している環境で、名前ベースのバーチャルホストをHTTPSでも有効にして、すべてのサイトをHTTPS化しました。パソコンのブラウザで確認したときは、どのサイトも問題なくHTTPSで表示されたのですが、2011年ごろに買ったAndroid端末でサイトを見ようとしたところ、なんと同居している別のサイトが表示されてしまいました。

HTTPSの場合、アクセスしたいサイトのドメイン名すら暗号化された状態でサーバにリクエストが届くため、クライアントがアクセスしたいドメイン名をサーバへ伝えるために、TLSのSNI（Server Name Indication）拡張機能が必要となります。iOS3以前のSafariや、Android2.3、WindowsXP上のIEなど、クライアントの端末が著しく古く、SNIに対応していない場合は、アクセスしたいドメイン名がサーバに伝わらず、サーバ側のデフォルトのホストが応答してしまうのです。

対策としてはサーバにIPアドレスを追加して、サイトごとに別々のIPアドレスを割り振ってやるか、もしくはSNI非対応端末をサイトのサポート対象から外す@<fn>{strict}か、のどちらかです。

//footnote[strict][Apache2.4の場合は、SSLStrictSNIVHostCheckディレクティブをオンにしておくと、SNI非対応端末がアクセスしてきたときに、デフォルトホストを出すのではなく、接続自体を拒否して403 Forbiddenになります。 @<href>{https://httpd.apache.org/docs/current/mod/mod_ssl.html#sslstrictsnivhostcheck}]

== もっとSSL/TLSを学びたいときは

「はじめに」に書いたとおり、新しい技術を学ぶとき、私たちの理解度は「分かった！」「分かってなかった…」という上下をくり返しながら、ゆるやかに上がっていくものです@<fn>{heavy}。本書を通してSSL/TLSを学び、最初の「分かった」まで辿りつけましたでしょうか？

//footnote[heavy][筆者も本書を書きながら、ずっと「SSL/TLSわかったー！」「私はSSL/TLSについて多大な勘違いをしていたいのでは…？」「いや、SSL/TLSわかってきたかも」「もうだめだ、SSL/TLSのことは何一つわからない」「わか、わかった？わかっ…あ、いや、わかっ…？」という上下をくり返しました]

最初の一歩は、小さな一歩です。でもとても素晴らしい一歩です。本書は初心者が挫折せずに最初の「分かった」へ辿りつけるところを目指したので、省略した部分もかなり多く、説明は概略の範囲にとどまっています。本書を読み終えて、もっとSSL/TLSについて知りたくなったら、次の本をお勧めします。

 * プロフェッショナルSSL/TLS　Ivan Ristić、齋藤孝道（監訳）
 ** @<href>{https://www.lambdanote.com/products/tls}
 * 暗号技術入門 第3版　結城浩
 ** @<href>{https://www.hyuki.com/cr/}
 * マスタリングTCP/IP SSL/TLS編　Eric Rescorla、齋藤孝道、古森貞、鬼頭利之
 ** @<href>{https://www.amazon.co.jp/dp/4274065421}

一回も空振りをせずプロになった野球選手はいません。間違えることを恐れて学ばないより、これからも「分かった！」と「分かってなかった…」を繰り返して、しっぱいねこ@<fn>{sippai}を抱きしめては一歩ずつ進んでいきましょう。

//footnote[sippai][「技術をつたえるテクニック」の「【コラム】失敗すると「しっぱいねこ」が生まれる」より @<href>{https://booth.pm/ja/items/1316755}]
