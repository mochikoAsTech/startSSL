= Oracle Cloudのアカウントを作ろう

この章ではOracle Cloudというクラウドでアカウントを作ります。

SSLを理解するには、実際に手を動かしてやってみるのがいちばんです。

その下準備としてまずはアカウント作成からはじめましょう。

//pagebreak

== サイトを作るのにどうしてサーバがいるの？

HTTPSのサイトを作るのに、必要な材料は次の3つです。

 * ウェブサーバ
 * ドメイン名
 * SSL証明書

ところで、どうしてサイトを作りたいだけなのに、ウェブサーバが必要なのでしょう？

そもそもですが、サーバとは@<ttb>{クライアントに対してサービスを提供するもの}です。居酒屋にあるビアサーバに「ビールをください」というリクエストを投げる…つまりコックを「開」の方へひねると、ビールというレスポンスが返ってきます。同様にあなたがブラウザでURLを入力したり、リンクをクリックしたりして、ウェブサーバに対して「ウェブページを見せてください」というリクエストを投げたら、ウェブページというレスポンスが返ってきます。（@<img>{beerServerAndWebServer}）

//image[beerServerAndWebServer][クライアントに対してサービスを提供するのがサーバ][scale=0.8]{
//}

つまり、せっかくHTMLや画像でウェブサイトのコンテンツを作っても、そのコンテンツを提供するウェブサーバがなければ、サイトはあなたのパソコンの中でしか見られず、インターネットで公開できないのです。@<fn>{startAWS}

//footnote[startAWS][サーバについては、はじめようシリーズの2作目、「AWSをはじめよう」の「CHAPTER1 インフラとサーバってなに？」で、より詳しく解説しています。仮想サーバと物理サーバ、クラウドとオンプレミス、ホストサーバとゲストサーバなどサーバ周りの用語をもう少し理解したい！という方はそちらも併せて読んでみてください]

というわけでウェブサイトをインターネットで公開するために、まずはウェブサーバを立てましょう。

== サーバを立てるにはお金が必要？

ウェブサイトを公開するにはサーバが必要です。そしてサーバを立てるには、普通はお金がかかります。ですがオラクルが提供している「Oracle Cloud（オラクル クラウド）」というサービスには、なんと有効期限なしで@<ttb>{ずっと無料で使えるAlways Free}という枠があります。Always Freeの範囲@<fn>{alwaysFreePlan}内であれば、サーバも無料で立てられます。

//footnote[alwaysFreePlan][Always Freeの範囲については、@<href>{https://www.oracle.com/jp/cloud/free/}を確認してください]

さらにAlways Freeとは別に、@<ttb>{30日間だけ有効な300ドル分の無償クレジット}も付いてきますので、Always Freeの範囲外のサービスはそちらで試せます。本書ではこのAlways Freeと、無償クレジットの範囲内でOracle Cloudを利用していきます。

Oracle Cloudは名前のとおりオラクルが提供しているクラウドです。あなたが「ウェブサイトを公開したいなぁ…だからサーバが必要だ！」と思ったとき、従量課金で、すぐに使えて、性能や台数の増減も簡単にできるのがクラウドです。Oracle Cloudなら、ブラウザでぽちぽちとスペックを選んでいくだけで、すぐにサーバが立てられます。

== なんでAWSじゃなくてOracleのクラウドを使うの？

クラウドはOracle Cloudだけではありません。かの有名なAWSことAmazon Web Servicesや、GoogleのGoogle Cloud Platform@<fn>{gcp}、MicrosoftのAzure@<fn>{azure}、その他にも国内クラウドとしてさくらインターネットがやっているさくらのクラウド@<fn>{sakura}、お名前.comでお馴染みGMOグループのGMOクラウド@<fn>{gmoCloud}などなど、たくさんのクラウドが存在しています。

//footnote[gcp][@<href>{https://cloud.google.com/}]
//footnote[azure][@<href>{https://azure.microsoft.com/ja-jp/}]
//footnote[sakura][@<href>{https://cloud.sakura.ad.jp/}]
//footnote[gmoCloud][@<href>{https://www.gmocloud.com/}]

2019年11月時点、クラウド市場ではAWSがシェア約40%でトップを独走中@<fn>{cloudShare}です。そのため仕事でAWSを使ったことがある、あるいはこれから使う予定だ、というエンジニアも多いと思います。

//footnote[cloudShare][IaaS＋PaaSクラウド市場、AWSの首位ゆるがず。AWS、Azure、Google、Alibabaの上位4社で市場の7割超。2019年第3四半期、Synergy Research Group － Publickey @<href>{https://www.publickey1.jp/blog/19/iaaspaasawsawsazuregooglealibaba4720193synergy_research_group.html}]

しかし最近は、Alibaba CloudやOracle Cloudといった後発のクラウド事業者も追い上げを見せています。こうした新興のクラウドは、先を行くAWSを見て学んだ上で生まれてきただけあって、よりスマートな作りになっているのがいいところです。

本来であれば、クラウドを選定する際の基準は、そのクラウド上で動かすサービスの性質によって異なるはずです。あなたが動かしたいサービスには、一体どのクラウドが適しているのでしょうか？

本書では次の2つを選定基準として、それに適したOracle Cloudで学びを進めていきたいと思います。

 * SSL証明書を自分で取得して設置する一通りの流れを試したい
 * できるだけお金をかけずに無料で試したい

== Oracle Cloudでアカウント登録

先ずはOracle Cloudのアカウントを作ります。お手元に次の2つを用意してください。

 * クレジットカード
 * SMS@<fn>{sms}受信が可能な携帯電話（電話番号認証で使用するため）

なお本書では、前述のとおりAlways Freeと300ドル分の無償クレジットという無料枠の範囲内で、Oracle Cloudを利用していきます。クレジットカードの登録は主に本人確認のために行なうもので、無料アカウントから有償アカウントへ手動でアップグレードしない限り、勝手に課金はされないので安心してください。

//footnote[sms][ショートメッセージサービスの略。宛先に電話番号を指定してメッセージを送れるサービス]

=== 無料でアカウントを作ろう

「Oracle Cloud 無料」で検索（@<img>{startSSL_27}）したら、いちばん上の［Oracle Cloud Free Tier | Oracle 日本］@<fn>{freeTier}をクリックします。

//image[startSSL_27][「Oracle Cloud 無料」で検索][scale=0.6]{
//}

//footnote[freeTier][@<href>{https://www.oracle.com/jp/cloud/free/}]

Oracle Cloud Free Tier@<fn>{nameOfFreeTier}のページが表示されたら、［今すぐ始める（無償）］をクリックします。（@<img>{startSSL_28}）

//footnote[nameOfFreeTier][ずっと無料のAlwaysFreeと、30日間だけ有効な300ドル分の無償クレジット、この2つを総称して「Free Tier（無償ティア）」と呼ぶようです]

//image[startSSL_28][［今すぐ始める（無償）］をクリック][scale=0.7]{
//}

［Oracle Cloud へのサインアップ］と表示されたら、［電子メール・アドレス］と［国/地域］を入力して、使用条件を確認した上で［次］をクリックします。（@<img>{startSSL_29}）

後で分からなくならないように、登録した内容を@<table>{oracleAccount}にメモしておきましょう。

//table[oracleAccount][Oracle Cloudに登録した情報]{
項目	例	あなたが登録した情報　　　　　　　
------------------------------------
電子メール・アドレス	startdns.01@gmail.com	
国/地域	日本	
//}

//image[startSSL_29][入力したら［次］をクリック][scale=0.8]{
//}

次は［アカウント詳細の入力］です。今回は仕事ではなく個人での利用ですので［アカウント・タイプ］は［個人使用］を選択してください。［クラウド・アカウント名］には@<ttb>{任意のアカウント名}を入力します。［クラウド・アカウント名］には英字小文字と数字のみ使えます。記号や英字大文字は使えないので注意してください。筆者は@<code>{startdns01}にしました。（@<img>{startSSL_30}）

//image[startSSL_30][［クラウド・アカウント名］には任意の名前を入力][scale=0.8]{
//}

［ホーム・リージョン］は［日本東部(東京)］を選択します。Oracle Cloudは世界の各地域にデータセンターを所有しており、サーバはそのデータセンターの中で元気に動いています。この［ホーム・リージョン］とは、@<ttb>{どの地域のデータセンターを使うか？を指定するもの}です。

ウェブサイトにアクセスするとき、パソコンのある場所からサーバまで物理的に距離が遠いと、それだけ通信にも時間がかかって応答時間も遅くなります。日本国内向けにウェブサイトを開設する場合は、基本的にこの［日本東部(東京)］のリージョンを選びましょう。［ホーム・リージョン］で［日本東部(東京)］を選択していても、その他のリージョンも利用できますので安心してください。（@<table>{oracleAccountType}）

//table[oracleAccountType][Oracle Cloudに登録した情報]{
項目	例	あなたが登録した情報　　　　　　　
------------------------------------
アカウント・タイプ	個人使用	
クラウド・アカウント名	startdns01	
ホーム・リージョン	日本東部(東京) 	
//}

この@<ttb>{［ホーム・リージョン］は後から変更ができません}。そして@<ttb>{Always Freeは、選択した［ホーム・リージョン］においてのみ利用可能}です。

2020年2月現在、Oracle Cloudの［日本東部(東京)］のリージョンは人気が高く、Always Free向けのリソースが不足していてサーバが立てられない、という事態がしばしば起きています。［米国東部(アッシュバーン)］をホーム・リージョンにすれば、このリソース不足は回避できますので、Always Freeを確実に使いたい方は、［ホーム・リージョン］で［米国東部(アッシュバーン)］を選択してください。本書ではAlways Free向けのリソースが不足していた場合は、無償クレジットを使用してサーバを立てますので、［日本東部(東京)］を選択して問題ありません。

続いて名前や住所を入力していきます。入力内容は日本語表記で構いません。個人利用なのですが［部門名］が必須であるため、ここでは「個人」と入力しておきましょう。［名］、［姓］、［部門名］、［住所］、［市区町村］、［都道府県］、［郵便番号］のすべてを入力してください。（@<img>{startSSL_31}）

//image[startSSL_31][名前や住所を入力][scale=0.8]{
//}

では最後に［モバイル番号］です。国番号は［日本(81)］を選択して、自分の携帯電話番号を入力します。このとき電話番号の先頭の0は不要です。例えば「090-○○○○-○○○○」という携帯電話番号であれば「@<ttb>{90}-○○○○-○○○○」と入力してください。携帯電話番号を入力したら［次: モバイル番号の確認］をクリックします。（@<img>{startSSL_32}）

//image[startSSL_32][携帯電話の番号を入力][scale=0.8]{
//}

数分以内に［Your Oracle Cloud verification code is ○○○○○○○.］と書かれたSMSが、入力した携帯電話番号宛てに届きます。（@<img>{startSSL_34}）

//image[startSSL_34][コード（7桁の数字）がSMSで届いた][scale=0.4]{
//}

SMSで届いた7桁の数字を［コード］に入力して、［コードの確認］をクリックします。（@<img>{startSSL_33}）

//image[startSSL_33][SMSで届いた数字を［コード］に入力して［コードの確認］をクリック][scale=0.6]{
//}

=== 〈トラブル〉どうしてもSMSが届かない！そんなときは？

携帯電話番号を入力したのにSMSが届かないときは、まず自分が契約している携帯キャリアの迷惑メール設定で、SMSを@<ttb>{スパムとしてはじく設定をしていないか}確認してみましょう。例えば海外の事業者から送信されたSMSを拒否する設定になっていたり、海外からの着信を拒否する設定になっていると、SMSが届かないことがあるようです。@<fn>{smsFromOversea}

//footnote[smsFromOversea][「Oracle CloudのSMSは海外の事業者から届く」という確証がある訳ではないです。あくまでSMSが届かないときによくある話だと思ってください]

ちなみに筆者の場合は、特に設定変更をせず同じ番号で2回試してみたのですが、最初は届かず、2回目でようやく届きました。

迷惑メールの設定を確認した上で何回か試して、それでもSMSが届かなかったら、ページ下部の［サポートが必要ですか。ご連絡ください: チャット・サポート］からサポートにチャットで問い合わせてみましょう。残念ながら英語でしか対応してもらえませんが、"I am trying to register on Oracle Cloud. But I can't receive SMS. What should I do?"（アカウント登録しようとしてるけどSMSが届かないの、どうしたらいい？）という感じで聞いてみましょう。すぐに「じゃあ登録情報をこのチャットで教えて。そうしたらこちらでコードを発行して、このチャットで伝えてあげる」（意訳）とサポートしてもらえます。

=== パスワードと支払情報の登録

正しいコードを入力すると、［パスワードの入力］が表示されます。［パスワード］と［パスワードの確認］を入力して、［次: 支払情報］をクリックします。（@<img>{startSSL_35}）

//image[startSSL_35][パスワードを入力して［次: 支払情報］をクリック][scale=0.8]{
//}

パスワードを入力すると、今度は［支払情報］のページが表示されます。

繰り返しお伝えしているとおり、Oracle CloudにはAlwaysFreeと無償クレジットという無料枠があります。本書ではこの無料枠の範囲内でOracle Cloudを使っていきますが、それでもクレジットカードは登録しておく必要があります。

なお［支払情報］のページに記載されているとおり、この後、管理画面で［アカウントのアップグレード］という作業をして、有償アカウントへ切り替えない限り、請求は絶対に発生しません@<fn>{upgrade}ので安心してカード情報を登録してください。

//footnote[upgrade][300ドル分の無償クレジットを使い切るか、あるいはアカウントを作ってから30日が経過すると、メールでお知らせが届きます。そこからさらに30日の間に有償アカウントへアップグレードしなければ、Always Freeのサービスを除いて、無償クレジットで作ったサーバやデータは削除されます。AWSのように、サーバを削除し忘れたまま無料期間が終わって、うっかり課金されてしまった…という事態は、Oracle Cloudでは起きないので安心してください]

［クレジット・カード詳細の追加］をクリック（@<img>{startSSL_36}）します。

//image[startSSL_36][［クレジット・カード詳細の追加］をクリック][scale=0.8]{
//}

［ご注文者様情報］はそのままで変更不要です。［カード情報］の［カードの種類］を選択し、［カードの番号］、［有効期限］、［CVN］を入力したら［Finish］をクリックします。（@<img>{startSSL_37}）@<fn>{creditCard}

//footnote[creditCard][Oracle Cloudでは、クレジットカード登録時に「1ドル認証」と呼ばれる認証方法で、そのクレジットカードが決済可能かをチェックしています。実際に請求は行なわれないのですが、クレジットカードによってはこの1ドル認証を不審な決済と判断して通さないため、それによってエラーが発生することがあるようです。その場合は別のクレジットカードで試すか、Oracle Cloudのチャット・サポートで問い合わせてみてください]

//image[startSSL_37][カード情報を入力して［Finish］][scale=0.4]{
//}

［クレジット・カード詳細をご提供いただきありがとうございます。］と表示（@<img>{startSSL_38}）されたら、支払い情報の登録は完了です。Oracle CloudのService Agreement@<fn>{serviceAgreement}を確認した上で、チェックボックスにチェックを入れて、［サインアップの完了］をクリックします。

//footnote[serviceAgreement][@<href>{https://www.oracle.com/goto/oraclecsa-jp-en}]

//image[startSSL_38][チェックを入れて［サインアップの完了］をクリック][scale=0.8]{
//}

これでOracle Cloudのアカウント登録の手続きはおしまいです。［アカウントの設定が完了するまでお待ちください。］と表示（@<img>{startSSL_40}）されます。準備が整うとサインイン画面にリダイレクトされますが、この［アカウントの設定が完了するまでお待ちください。］の画面でかなり時間がかかるので、一度ブラウザを閉じてしまって構いません。頑張った自分を褒めてあげて、一旦休憩にしましょう。

//image[startSSL_40][アカウント登録の手続きはおしまい][scale=0.8]{
//}

数時間後@<fn>{2hours}、［Your Oracle Cloud Account is Fully Provisioned］という件名で、準備完了を知らせるメールが届きます。メール本文の［Sign In to Oracle Cloud］をクリックしましょう。（@<img>{startSSL_39}）

//footnote[2hours][筆者の場合は、メールが届くまで約2時間半かかりました]

//image[startSSL_39][数時間後、準備完了を知らせるメールが届く][scale=0.8]{
//}

=== Oracle Cloudのコンソールにサインイン

メールの［Sign In to Oracle Cloud］をクリックすると、コンソールへのサインイン@<fn>{SignInLogIn}画面が表示されます。（@<img>{startSSL_41}）

［ユーザー名］には先ほど登録したメールアドレスを入力します。@<fn>{username}［パスワード］を入力して、［サイン・イン］をクリックしてください。

//footnote[SignInLogIn][日本語だとログインの方が馴染みがあるかも知れませんが、サインインはログインと同じ意味です]
//footnote[username][メールにも書いてありますが、ここでの［ユーザー名］とは［クラウド・アカウント名］（筆者の場合は@<code>{startdns01}）ではなく、［メールアドレス］のことです。紛らわしいのでご注意ください]

//image[startSSL_41][［ユーザー名］と［パスワード］を入力して［サイン・イン］][scale=0.8]{
//}

おめでとうございます！Oracle Cloudの管理画面、コンソールにサインインできました。

//image[startSSL_42][コンソールにサインインできた！][scale=0.8]{
//}

なお今後、コンソールにサインインしたくなったら、いちいちOracle Cloudからのメールを探してリンクを踏む必要はありません。まずはOracleのトップページ@<fn>{oracleSite}を開いて、右上の人物マークをクリックします。そして［クラウドにサインイン］をクリックしてください。

//footnote[oracleSite][@<href>{https://www.oracle.com/jp/}]

//image[startSSL_44][右上の人物マークをクリックして［クラウドにサインイン］][scale=0.8]{
//}

サインインのページ@<fn>{signIn}で［Account］の欄にクラウド・アカウント名@<fn>{cloudAccount}を入力して［Next］をクリックすれば、メールのリンクを踏んだときと同じ［サイン・イン］のページにたどり着けます。あとは同じように［ユーザー名］にはメールアドレスを、［パスワード］にはパスワードを入力して、［サイン・イン］をクリックするだけです。

//footnote[signIn][@<href>{https://www.oracle.com/cloud/sign-in.html}]
//footnote[cloudAccount][筆者の場合は@<code>{startdns01}です。アカウント登録時に、あなたの［クラウド・アカウント名］をメモしているはずですので、P24に戻って確認してみましょう]

//image[startSSL_43][［Account］の欄にクラウド・アカウント名を入力して［Next］をクリック][scale=0.8]{
//}
