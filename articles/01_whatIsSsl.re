= SSL/TLSとは？

SSLってなに？TLSってなに？
なんでHTTPSにしなきゃいけないの？

まずは素朴な疑問を解きほぐして、SSLをはじめる意味を見つけましょう。

//pagebreak

== SSL/TLSってなんですか？

SSL（Secure Socket Layer）/TLS（Transport Layer Security）とは、インターネット上で安全にデータを送受信するための約束事（プロトコル@<fn>{protcol}）です。

//footnote[protcol][例えば手紙は「メッセージを書いた便せんを封筒に入れて、表に宛先、裏に差出人を書き、重さに応じた切手を貼ってポストに入れる」という取り決めに従えば、きちんと相手に届きます。手紙の例と同じように、インターネットで通信を行なう際、どんなデータをどんな方法で送受信するのか、という「約束事」のことをプロトコルと呼びます。SSLもTLSもプロトコルですし、HTTPやHTTPS、DNSもSMTPもプロトコルです]

SSLもTLSもあくまでプロトコル、つまり通信するための「約束事」なので、実際に通信するときは、そのプロトコルに従って実装されたソフトウェアを使います。SSL/TLSでは、OpenSSLというオープンソースのソフトウェアを使うことがほとんど@<fn>{opensslCommand}です。

//footnote[opensslCommand][@<chapref>{04_getSSLCertificate}で、SSL証明書を取得するために使うコマンドも、opensslコマンドです]

=== SSLとTLSはどういう関係？

SSLとTLSは別々の名前ですが、その役割に大きな違いはありません。「SSL3.0」からバージョンアップする際に、「SSL3.1」ではなく「TLS1.0」という新しい名前が付けられました。つまり「TLSはSSLの後継バージョン」ということです。

ちなみに名前がまだSSLだったときの最後のバージョン「SSL3.0」は、重大な脆弱性@<fn>{zeizyakusei}が見つかり、2015年のRFC 7568@<fn>{rfc7568}でもう使わないよう「Do Not Use SSL Version 3.0」と示されています。

//footnote[zeizyakusei][脆弱性（ぜいじゃくせい）というのは悪用が可能なバグや設定不備のことです]
//footnote[rfc7568][Deprecating Secure Sockets Layer Version 3.0 @<href>{https://tools.ietf.org/html/rfc7568}]

ですがSSLという言葉の認知度が高く、TLSと呼んでもピンとこない人の方が多いため、現状は分かりやすさと正確さを両立させてSSL/TLSと併記することが多いです。

本書ではSSL/TLSのことを指して、SSLという言葉を使用します。

=== SSLイコールHTTPSではない

サイト全体を「https://」から始まるURLにすることを、「常時SSL化」のように呼ぶため、皆さんの中にはSSL＝HTTPSだと思っている人がいるかも知れません。

HTTPとSSLを組み合わせて使うことで、通信を保護するプロトコルがHTTPS（Hypertext Transfer Protocol Secure）です。ですが、SSLはHTTPSにおいてのみ使われるプロトコルではありません。例えばサーバにファイルをアップするときのFTPとSSLを組み合わせて使うFTPS（FTP over SSL）や、メール送信のSMTPとSSLを組み合わせて使うSMTPS（SMTP over SSL）など、HTTPS以外にもSSLが使われている場面はたくさんあります。

繰り返しになりますが、SSLはインターネット上で安全にデータを送受信するためのプロトコルです。上位のアプリケーション層@<fn>{osi}がHTTPであれ、FTPであれ、SSLを組み合わせて使うことでデータを安全に送受信できるようになるのです。

SSL＝HTTPSではない、ということを踏まえた上で、ここからは「サイトをHTTPS化する」ことについて学んでいきましょう。

//footnote[osi][OSI参照モデルのアプリケーション層のこと。エンジニア諸氏は誰しも、大学の授業や新卒研修で一度は「アプセトネデブ」という語呂合わせを聞いたことがあるのでは…]

== 「サイトをHTTPS化する」とは何か？

そもそもですが「サイトをHTTPS化する」とは、なんでしょう？

本書では、「サイトのHTTPS化」を、@<ttb>{ウェブサイト全体を「https://」から始まるURLにすること}と定義します。これは「常時SSL化」や「常時SSL/TLS化」、「フルSSL化」、「AOSSL（Always On SSLの略）」といった言葉で表現されることもあります。

2014年ごろはまだ、お問い合わせや会員登録など、個人情報を入力したり表示したりする一部のページのみをHTTPSにしているサイトが多く存在していました。ですがGoogleがHTTPSを強く推奨しはじめたことで、「一部ページだけに限らず、ウェブサイト全体をHTTPSにしよう」という動きが段々と活発になっていきました。

大手サイトが次々とHTTPS化しはじめたのが、2016年から2017年ごろだったと記憶しています。たとえばクックパッドは2017年1月@<fn>{cookpad}、日経新聞電子版は2017年8月@<fn>{nikkei}に、それぞれHTTPS化が完了したことを発表しています。

//footnote[cookpad][@<href>{https://techlife.cookpad.com/entry/2017/04/19/190901}]
//footnote[nikkei][@<href>{https://www.nikkei.com/topic/20170808.html}]

そして2020年現在、HTTPS化の動きは、大手サイトだけでなくあらゆるサイトを対象にさらに進みつつあります。

== どんなサイトでも必ずHTTPSにしなきゃだめ？

でも企業がやっているネットショップならまだしも、個人情報をやり取りするわけでもない、ただ個人の日記を公開しているだけのサイトも、HTTPS化しなければいけないのでしょうか？

確かにサイトをHTTPS化すると「通信が暗号化により保護される」という大きなメリットがあります。2014年より前は「HTTPS化すれば通信が保護される。けれど特に保護すべきやりとりでなければ、HTTPS化しなくても悪いことが起きる訳ではない」という状況でした。

== HTTPのままだと起きるデメリット

ですが2020年現在は、HTTPS化しないでいるとさまざまなデメリットが発生します。どんなデメリットが起きるのか、具体的に解説していきましょう。

=== サイトが「安全でない」と表示されてしまう

GoogleはHTTPからHTTPSへの移行を強く推進しています。その施策の1つとして、Googleが提供するウェブブラウザ「Google Chrome」では、2018年7月にリリースされたバージョン68から、HTTPSでないページに対して「保護されていない通信」という表示をするようになりました。

Chromeでサイトを開いて、URLが「http://」で始まるものだった場合、次のようにURLの左側に「保護されていない通信」と表示（@<img>{startSSL_83}）されます。

//image[startSSL_83][ChromeでHTTPのサイトを開くと「保護されていない通信」と表示される][scale=0.6]{
//}

サイトを見たとき、URLの真横に「保護されていない通信」と表示されたら、「なんだか危なさそう…見ない方がいいのかも…？」と心配になってしまいますよね。ChromeだけでなくFirefoxも、HTTPのサイトに対して錠前に赤い斜め線が入ったマークの表示（@<img>{startSSL_84}）を行っており、サイトをHTTPS化しないことで、エンドユーザにサイトが「安全でない」と思われてしまう状況にあります。

//image[startSSL_84][FirefoxでHTTPのサイトを開くと錠前に赤い斜め線が入ったマークが表示される][scale=0.6]{
//}

=== Wi-Fiスポットなどでセッションハイジャックされる恐れがある

たとえば、買い物をしようと思って楽天のサイトを開くと、今日はまだログインしていないのに、ログイン済みのページが表示されることがあります。これは以前ログインした際に、サイトからCookieで渡された「セッションID」（一時的な通行証のようなもの）をブラウザが保持していて、再びサイトを開いたときに提示することで、ログイン済みのユーザーとして扱われるからです。

ログインページだけがHTTPSになっているサイトだと、それ以外のページをHTTPで開いたとき、CookieにSecure属性が付いていなければ、この「セッションID」は暗号化されない状態で送信されてしまいます。では、誰でも使えるWi-Fiスポットに、スマホやタブレットを繋いだ状態で、HTTPのページを開いて「セッションID」が送られたらどうなるでしょう？

なんと同じWi-Fiにつないでいる、悪意の第三者によって、暗号化されていない「セッションID」を盗まれ、なりすましでサイトにログインされる恐れがあります。これが「セッションハイジャック」と呼ばれる攻撃です。

こうした攻撃を防ぐには、サイト全体をHTTPSにして、常にCookieの「セッションID」を保護しておく必要があります。またログインなどが一切ない、公開情報しか載せていないサイトであっても、Wi-Fiスポットなどで見知らぬ誰かに「あの人はどんなサイトを見ているのだろう？」とデータを窃視されるリスクもあります。

例えば「妊活情報のブログを長時間読んでいた」「特定の病気について調べていた」など、どんなサイトを見ていたのか？という情報の中にも、人に知られたくないことはたくさんあります。サイトとの通信がHTTPSで保護されていれば、このような情報を盗み見られるリスクを低減できます。

=== 相対的に検索順位が下がる

さらに、インターネット全体でHTTPS化が進むことによって、HTTPのままでいるサイトに起きるデメリットもあります。

Googleは「HTTPS everywhere」、つまり「（お問い合わせや会員登録といった一部のページに限らず）すべてをHTTPSで！」を提唱しており、2014年8月の時点で既に、HTTPSに対応しているウェブサイトを検索ランキングで優遇する方針も発表@<fn>{rankingSignal}しています。

//footnote[rankingSignal][Google ウェブマスター向け公式ブログ [JA\]: HTTPS をランキング シグナルに使用します @<href>{https://webmaster-ja.googleblog.com/2014/08/https-as-ranking-signal.html}]

Googleのランキングアルゴリズムでは、「サイトがHTTPS化されているか」が指標のひとつとなっています。もちろんたくさんある指標の中のひとつで、他の指標ほどウェイトは大きくない、とされていますが、競合サイトのHTTPS化が進む中、自分のサイトだけHTTPのままでいると、相対的に検索順位が下がる可能性があります。

=== 周りがHTTPSになるとリファラが取れなくなる

こちらはGoogleアナリティクスなどを使って、サイト流入元の情報を確認している方にとって、重要と思われるデメリットです。

自社のサイトがHTTPだと、HTTPSの他社サイトからリンクを踏んで飛んできた場合に、リファラ（利用者が直前に訪問していたサイトの情報）を取得することができません。HTTPのサイトでGoogleアナリティクスを使っている方は、実際にGoogleアナリティクスのページを開いて、集客の「参照元/メディア」を確認してみてください。アクセス元が「（direct）/（none）」と表示されて、どこから飛んできたのか分からないものがありませんか？その中には、ブラウザのブックマークや、メール内のリンクから飛んできた、本当に「直前に訪問していたサイトが存在しないもの」だけでなく、HTTPSのサイトから飛んできたアクセスも含まれています。

今後、周囲のサイトのHTTPS化が進んで、自社のサイトだけがHTTPで取り残されると、この「リファラが取得できる割合」はますます下がっていくことになります。自社のサイトをHTTPSにすれば、他社のHTTPSサイトから飛んできた場合でも、リファラを取得できるようになります。

== HTTPS化すると得られるメリット

HTTPのままでいると起きるデメリットだけでなく、HTTPS化すると得られるメリットももちろんあります。

=== HTTP/2との組み合わせで速度が向上するケースもある

かつては、HTTPSにすると、暗号化と復号のオーバーヘッドでHTTPのときよりもサイトが遅くなる、というのが常識でした。しかし、サーバ側、クライアント側ともにCPUの性能が向上したことで、2020年現在、もはやオーバーヘッドは重要視するほどではなくなっています。@<fn>{sslAccelerator}

//footnote[sslAccelerator][サーバの手前に配置して、暗号化や復号だけを行なう専用機器の「SSLアクセラレータ」を使う話も、最近はほぼ聞かなくなりました]

またHTTPSにすることで、HTTP/2というHTTPプロトコルの次期バージョンを利用できる@<fn>{browserNeeds}ようになります。SSLのオーバーヘッドは特にハンドシェイクに集中しているため、長期にわたって接続したままで、リクエストとレスポンスを多重化できるHTTP/2と組み合わせると、ハンドシェイクの回数が減る分だけ接続効率が上がります。ページの作りによってもちろん向き不向きがあり、HTTPSにしたことで表示速度が落ちるケースもあると思います。たとえばサイズが小さな画像を大量に表示するようなページ（@<img>{startSSL_124}）@<fn>{httpVsHttps}は、HTTP/2の恩恵を受けやすく、速度の向上が期待できます。

//footnote[browserNeeds][HTTP/2は、仕様上はHTTPにも対応していますが、ブラウザ側がHTTPSでしかHTTP/2を利用できないようになっているため、実質的にはHTTP/2を使う際はHTTPSが必須となります]

//image[startSSL_124][HTTP vs HTTPS Test][scale=0.6]{
//}

//footnote[httpVsHttps][HTTP vs HTTPS Test @<href>{https://www.httpvshttps.com/}]

さらにTLS1.3になると、TLS1.2と比べてハンドシェイクに要するやりとりの回数や所要時間が大幅に短くなり、さらなる速度改善が見込まれます。

=== SameSiteの変更に対応できる

2020年2月にリリースされたChromeのバージョン80@<fn>{sameSite}から、CookieのSameSiteの設定が従来より厳しくなり、いままで設定なしで使えていたクロスサイトCookieが、デフォルトでは使えないように順次変更されていくことが発表されました。

ですが「SameSite=None; Secure」の設定をすれば、クロスサイトCookieは引き続き利用できます@<fn>{samesiteCookie}。そしてSecure属性を追加するには、HTTPSでの接続が必須です。

//footnote[sameSite][@<href>{https://developers-jp.googleblog.com/2019/11/cookie-samesitenone-secure.html}, @<href>{https://developers-jp.googleblog.com/2020/02/2020-2-samesite-cookie.html}]
//footnote[samesiteCookie][2020年2月時点ではこの方法で回避できますが、将来的には制約がより厳しくなる可能性ももちろんあります]

このように、HTTPSであればSameSiteの変更にも対応できる、というメリットがあります。

=== 重要情報のアタリが付けにくくなる

これは自分のサイトだけでなく、インターネット上のサイト全体がHTTPSに対応したときに得られるメリットです。

流れていくデータのほとんどが平文な中で、たまに暗号化されたデータがやってくると、データを窃視していた悪意の第三者は「暗号化されているということは、あれは重要な情報だな！」とアタリを付けて狙うことができます。ですが、すべてのサイトがHTTPSになって、流れてくるデータがすべて暗号化されるようになれば、どれが重要なデータなのかアタリが付けにくくなります。大事なものも大事でないものもすべて同じ頑丈なアタッシュケースにしまって運べば、泥棒がどのアタッシュケースを狙えばいいのか分からなくなります。木は森に隠せ、という戦法です。

このように、HTTPのままだと起きるデメリット、HTTPSにすると得られるメリット、その両方があるのでどんなサイトもHTTPS化する意味がある、ということですね。

