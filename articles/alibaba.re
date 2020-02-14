= Alibaba Cloudでアカウント登録

== 無料でアカウントを作成

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

//image[startSSL_5][メールアドレスを確認して［通知］をクリック][scale=0.8]{
//}

［Alibaba Cloud Email Verification］という件名でメールが届きます。メールの本文に書かれているCodeをコピーしましょう。

//image[startSSL_9][Alibaba Cloudからメールが届いたらCodeをコピー][scale=0.8]{
//}

メールからコピーしたCodeを、［2.Please enter the verification code below.］の下の欄にペーストします。［認証］をクリックしてください。

//image[startSSL_7][メールからコピーしたCodeをペーストして［認証］をクリック][scale=0.8]{
//}

もし迷惑メールフィルタなどが原因でメールが届かないときは、［Use phone instead］をクリックすれば、メールアドレスの代わりに携帯電話の番号を登録して、SMSで確認コードを受信する方法でも認証できます。

//image[startSSL_8][携帯電話の番号を入力して［SMSで通知］をクリック][scale=0.8]{
//}

//image[startSSL_10][SMSでCodeが届いた][scale=0.6]{
//}

無事に認証が完了したらログインページが表示されます。先ほど登録したメールアドレスとパスワードを入力したら、［サインイン］をクリックします。

//image[startSSL_11][メールアドレスとパスワードを入力して［サインイン］][scale=0.8]{
//}

== 作ったアカウントでサインインする

サインインできたら、最上部の［Alibaba Cloud を始めるため、もう 1 つステップが必要です。請求先住所と支払い方法を追加してください。］の隣にある［進む  >>］をクリックします。

//image[startSSL_12][サインインできたら、最上部の［進む  >>］をクリック][scale=0.8]{
//}

ここからは無料トライアルを使うために必要な情報を入力していきます。

== Basic information

=== Account Type（アカウントの種類）

このアカウントは業務用ではなく、個人的な勉強のために使うので、Account Typeは［Personal account］を選択します。
450ドル相当のフリートライアルが可能だそうです。すごい。

//image[startSSL_13][Account Typeは［Personal account］を選択][scale=0.8]{
//}

=== Billing address（請求先住所）

続いて請求先の郵便番号、住所、氏名を入力します。@<fn>{address}

//footnote[address][キャプチャでは、郵便番号と住所はSBクラウドのオフィスをサンプルとして入力しています。実際はご自身の住所やお名前をきちんと登録してください。]

//image[startSSL_14][郵便番号、住所、氏名を入力する][scale=0.8]{
//}

=== Identity verification by phone（電話認証）

最後に携帯電話の番号を入力したら、［Verify］をクリックします。

//image[startSSL_15][携帯電話の番号を入力したら［Verify］をクリック][scale=0.8]{
//}

［Ali SMS］からSMSが届きます。

//image[startSSL_16][SMSでCodeが届いた][scale=0.6]{
//}

SMSに書いてあったCodeを、［Verification］の下の欄に入力します。［Verify］をクリックしてください。

//image[startSSL_17][SMSに書いてあったCodeを入力して［Veirfy］をクリック][scale=0.8]{
//}

［Verified］と表示されたら電話認証は完了です。もしこの番号で営業電話を受けたくなければ、［Alibaba Cloud may not call me to discuss deals and offers.］にもチェックを入れておきましょう。［Submit］をクリックします。

//image[startSSL_18][［Verified］と表示されたことを確認して［Submit］をクリック][scale=0.8]{
//}

=== Add a payment method（支払い方法の追加）

続いて支払い方法を追加します。Alibaba Cloudでは、AWSと同じように使った分だけ請求が来ます。本書では無料トライアルの範囲内でAlibaba Cloudを使っていきますが、支払い方法は登録しておく必要があります。

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

= Alibaba Cloudでサーバを立てよう

Alibaba Cloudのトップページ@<fn>{topPage}で、右上の［ログイン］をクリックします。

//footnote[topPage][@<href>{https://www.alibabacloud.com/}]

//image[startSSL_23][トップページで［ログイン］をクリック][scale=0.8]{
//}

ログインページを開いたら、さっき登録したメールアドレスとパスワードを入れて［サインイン］しましょう。@<fn>{login}

//footnote[login][ログインなの…サインインなの…もう何も分からない…]

//image[startSSL_24][さっき登録したメールアドレスとパスワードを入れて［サインイン］][scale=0.8]{
//}

サインインできたら［無料試用版］をクリックします。

［Alibaba Cloud 無料トライアル］のページで、［Elastic Compute Service (ECS) (2つから 1 つを選択)］の

バースト可能タイプ t5
1 コア CPU 1 GB メモリ12 ヶ月 無料トライアル
開発者向け費用対効果の高いパッケージ

を選んで、［無料トライアル］をクリックします。

//image[startSSL_25][［無料トライアル］をクリック][scale=0.8]{
//}

［データセンターのリージョン］を［日本（東京）］に変更します。各項目の設定が次のようになっている@<fn>{aliyun}ことを確認してください。（@<table>{selectEcs}）

//table[selectEcs][ECS設定]{
項目	設定　　　　　　　
------------------------------------
データセンターのリージョン	日本（東京）
ECS Instance    Typeecs.t5-lc1m1.small
ECS Instance    1コア CPU (Intel Xeon)
メモリ  1GB メモリ (DDR4)
ディスク    40GB SSD ディスク
データトラフィック  1MB インターネット帯域幅 (VPC)
オペレーティングシステム    Aliyun Linux 2
//}

//footnote[aliyun][ちなみにAliyunはAlibabaの雲（中国語のピンインでyún）、つまりCloudなのでAliyunのようです。]


［ECS Terms and Conditions および General Product Terms and Conditions を読み、内容に同意いたします。］にチェックを入れたら、［無料トライアル］をクリックします。

//image[startSSL_26][［データセンターのリージョン］を［日本（東京）］にして［無料トライアル］をクリック][scale=0.8]{
//}

• ecs.t5-lc1m1.small (12 か月間、40 GB ultra クラウドディスクまたは SSD ディスク、1 MB インターネット帯域幅)
