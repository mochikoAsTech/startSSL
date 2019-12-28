= SSLのサイトを作ってみよう

== Alibaba Cloudでアカウント登録

=== 無料でアカウントを作成

Googleで［Alibaba Cloud Free Trial］を検索（@<img>{startSSL_1}）。したら、上から4つめの［Alibaba Cloud 無料トライアル - 40 以上のプロダクトをお試し ...］をクリックします。2つめにもよく似た［Alibaba Cloud 無料利用枠 -製品やサービスを無料で体験でき ...］がありますが、そちらはまた別のサイト@<fn>{SBCloud}なので、ぐっとこらえて@<code>{https://www.alibabacloud.com › campaign › free-trial}と書いてある4つめの方をクリックしてください。

//image[startSSL_1][［Alibaba Cloud Free Trial］を検索][scale=0.8]{
//}

//footnote[SBCloud][@<code>{jp.alibabacloud.com}はSBクラウド（ソフトバンク株式会社とアリババグループの合弁会社）が日本国内向けに提供しているAlibaba Cloudで、@<code>{www.alibabacloud.com}はアリババグループがグローバルに提供しているAlibaba Cloudである（という理解を筆者はしています）。今回はグローバル向けの後者を使います。]

［Alibaba Cloud 無料トライアル］@<fn>{freeTrial}のページを開いたら、［無料アカウントの作成］（@<img>{startSSL_2}）をクリックします。

//footnote[freeTrial][@<href>{https://www.alibabacloud.com/ja/campaign/free-trial}]

//image[startSSL_2][［無料アカウントの作成］をクリック][scale=0.8]{
//}

［Create a new Alibaba Cloud account］と書かれた英語のページが表示されます。右上の［Intl - English］から言語選択を開いて、［International］の［日本語］@<fn>{SBCloud2}を選択します。

//footnote[SBCloud2][ちなみに［日本］の［日本語］を選ぶと、前述したSBクラウドの方のAlibaba Cloudでのアカウント作成ページに遷移してしまうのでご注意ください。]

//image[startSSL_3][［無料アカウントの作成］をクリック][scale=0.8]{
//}

［新しい Alibaba Cloud アカウントを作成する］と書かれた日本語のページになりました。それでは次の情報を入力して、会員規約やプライバシーポリシー等を確認した上でチェックボックスにチェックを入れたら［登録］をクリックしましょう。後で分からなくならないように、登録した項目をメモしておきましょう。（@<table>{alibabaAccount}）

//image[startSSL_4][入力してチェックを入れたら［登録］をクリック][scale=0.8]{
//}

//table[alibabaAccount][Alibaba Cloudに登録した情報]{
項目	例	あなたが登録した情報　　　　　　　
------------------------------------
国	日本	
メールアドレス	startdns.01@gmail.com	
パスワード	自作のパスワード	
//}

登録したメールアドレス宛てに確認コードを送信するよう書いてあるので［通知］をクリックします。

//image[startSSL_5][メールアドレスを確認して［通知］をクリック][scale=0.6]{
//}

［Alibaba Cloud Email Verification］という件名でメールが届きます。メールの本文に書かれているCodeをコピーしましょう。

//image[startSSL_9][Alibaba Cloudからメールが届いたらCodeをコピー][scale=0.6]{
//}

メールからコピーしたCodeを、［2.Please enter the verification code below.］の下の欄にペーストします。［認証］をクリックしてください。

//image[startSSL_7][メールからコピーしたCodeをペーストして［認証］をクリック][scale=0.6]{
//}

もし迷惑メールフィルタなどが原因でメールが届かないときは、［Use phone instead］をクリックすれば、メールアドレスの代わりに携帯電話の番号を登録して、SMSで確認コードを受信する方法でも認証できます。

//image[startSSL_8][携帯電話の番号を入力して［SMSで通知］をクリック][scale=0.6]{
//}

//image[startSSL_10][SMSでCodeが届いた][scale=0.6]{
//}

無事に認証が完了したらログインページが表示されます。先ほど登録したメールアドレスとパスワードを入力したら、［サインイン］をクリックします。

//image[startSSL_11][メールアドレスとパスワードを入力して［サインイン］][scale=0.6]{
//}

=== 作ったアカウントでサインインする

サインインできたら、最上部の［Alibaba Cloud を始めるため、もう 1 つステップが必要です。請求先住所と支払い方法を追加してください。］の隣にある［進む  >>］をクリックします。

//image[startSSL_12][サインインできたら、最上部の［進む  >>］をクリック][scale=0.8]{
//}

ここからは無料トライアルを使うために必要な情報を入力していきます。

==== Basic information

===== Account Type（アカウントの種類）

このアカウントは業務用ではなく、個人的な勉強のために使うので、Account Typeは［Personal account］を選択します。
450ドル相当のフリートライアルが可能だそうです。すごい。

//image[startSSL_13][Account Typeは［Personal account］を選択][scale=0.8]{
//}

===== Billing address（請求先住所）

続いて請求先の郵便番号、住所、氏名を入力します。@<fn>{address}

//footnote[address][キャプチャでは、郵便番号と住所はSBクラウドのオフィスをサンプルとして入力しています。実際はご自身の住所やお名前をきちんと登録してください。]

//image[startSSL_14][郵便番号、住所、氏名を入力する][scale=0.8]{
//}

===== Identity verification by phone（電話認証）

最後に携帯電話の番号を入力したら、［Verify］をクリックします。

//image[startSSL_15][携帯電話の番号を入力したら［Verify］をクリック][scale=0.8]{
//}

［Ali SMS］からSMSが届きます。

//image[startSSL_16][SMSでCodeが届いた][scale=0.6]{
//}

SMSに書いてあったCodeを、［Verification］の下の欄に入力します。［Verify］をクリックしてください。

//image[startSSL_17][SMSに書いてあったCodeを入力して［Veirfy］をクリック][scale=0.6]{
//}

［Verified］と表示されたら電話認証は完了です。もしこの番号で営業電話を受けたくなければ、［Alibaba Cloud may not call me to discuss deals and offers.］にもチェックを入れておきましょう。［Submit］をクリックします。

//image[startSSL_18][［Verified］と表示されたことを確認して［Submit］をクリック][scale=0.8]{
//}

===== Add a payment method（支払い方法の追加）

続いて支払い方法を追加します。Alibaba Cloudでは、AWSと同じように使った分だけ請求が来ます。本著では無料トライアルの範囲内でAlibaba Cloudを使っていきますが、支払い方法は登録しておく必要があります。

［Add］をクリックして、クレジットカードの情報を登録しましょう。

//image[startSSL_19][［Add］をクリックしてクレジットカードの情報を登録][scale=0.8]{
//}

カード情報を入力したら［Submit］をクリックします。

//image[startSSL_20][カード情報を入力したら［Submit］をクリック][scale=0.8]{
//}

こんな感じで「ちょっと待ってね…」と表示されたのちに…

//image[startSSL_21][ちょっと待ってね…の表示][scale=0.8]{
//}

［Success］と表示されたら、請求先住所と支払い方法の登録は完了です。これで無料トライアルが使えるようになりました！早速［Free Trial］をクリックして、HTTPSのサイトを乗っけるサーバを立ててみましょう。

//image[startSSL_22][［Success］と表示されたら登録完了][scale=0.8]{
//}

== Alibaba Cloudでサーバを立てよう

== ドメイン名の設定

== まずはHTTPでサイトを公開

== 証明書を取得しよう

=== 秘密鍵を作ろう
=== CSRを作ろう
=== 証明書の取得申請
=== 取得した証明書をサーバに置こう

== HTTPSでサイトを公開

= 基本
== SSLってなに？
== TLSってなに？
== SSLとTLSの違いは？
== SSLとSSHって似てる？何が違うの？
== HTTPSで始まるページで鍵のマークが壊れて表示された
== 種類
=== SSLサーバ証明書
=== SSLクライアント証明書
== どんなシーンで使われている？
== SSL証明書は全然違う2種類の仕事をしている
=== Webサイトで送受信する情報を暗号化すること
=== Webサイト運営者の身元を証明すること
== 鍵マークが壊れるケース
=== すべてHTTPで通信しているとき
=== HTTPSだけど一部がHTTPSじゃないとき
==== 画像とCSSの指定が絶対パスだった
== ウェブページが表示されるまで
=== 1往復で表示されるわけじゃない
== SSL証明書は何を証明してくれるのか？
=== ネットバンクの事例
== 認証局事業者の身元は誰が証明する？
=== 身元保証の連鎖をつなぐ中間CA証明書とルート証明書
== SSL証明書はどうしてあんなに値段に差があるの？
== 同じ「SSL証明書」という名前でも3つの種類がある
=== EV証明書
==== さよならグリーンバー
=== OV証明書
=== DV証明書
=== 3つの違いは何か？
=== ブラウザベンダーによるEV証明書の扱いの変化
== その他の証明書
=== 中間証明書
=== クロスルート証明書
== どの証明書を買えばいい？
=== ワイルドカード証明書
=== wwwありにリダイレクトしたいだけなのにwwwなしの証明書もいるの？
=== コモンネームが*.example.comの証明書はexample.comで使える？
==== SANs
=== Let'sEncrypt
== CDNと証明書
=== CDNを使ったら古い端末でサイトが見られなくなった
=== 同じサーバで複数サイトをHTTPS化したら古い端末で別サイトが表示された
=== SNI Server Name Indication
