= サーバを立ててHTTPでサイトを見てみよう

HTTPSのサイトを作るのに、必要な材料は次の3つです。

 * ウェブサーバ
 * ドメイン名
 * SSL証明書

まずはウェブサーバとドメイン名を用意して、HTTPでサイトを見てみましょう。

//pagebreak

== 事前準備

まずは、サーバを立てるときに必要なターミナルソフトを準備して、キーペアの作成を行ないます。Windows、Macの順番で手順を説明します。

=== Windowsでターミナル（RLogin）を準備する

Windowsのパソコンを使っている方は、サーバを立てる前に「ターミナル」と呼ばれる黒い画面のソフトをインストールしておきましょう。サーバにログインするときには、このターミナルを使います。ターミナルのソフトには色々な種類がありますが、本書ではRLogin@<fn>{rlogin}を使用します。RLoginのインストール方法は「AWSをはじめよう」@<fn>{boothAWS}で説明していますので、本書では省略します。インストールしたRLoginのフォルダは、デスクトップにあるものとします。

//footnote[boothAWS][@<href>{https://mochikoastech.booth.pm/items/1032590}]
//footnote[rlogin][@<href>{http://nanno.dip.jp/softlib/man/rlogin/}]

=== WindowsでSSHのキーペア（秘密鍵・公開鍵）を作成する

それではRLoginを使ってキーペアを作成します。起動したRLoginで［新規(N)］をクリックしてください。

//image[startSSL_45][［新規(N)］をクリック][scale=0.6]{
//}

左メニューの［プロトコル］を選択して、［認証キー(K)］をクリックします。

//image[startSSL_47][［プロトコル］を選択して［認証キー(K)］をクリック][scale=0.6]{
//}

［任意の名前が指定できます］に［startSSLKey］を入力して、［作成］をクリックします。

//image[startSSL_48][［startSSLKey］を入力して［作成］をクリック][scale=0.6]{
//}

［パスフレーズ］と［パス再入力］には何も入力せず、［OK］をクリックします。@<fn>{whatIsPassPhrase}

//footnote[whatIsPassPhrase][このパスフレーズは秘密鍵の保護に用いられます。パスフレーズを設定しなくてよいのか、についてはコラムで後述します]

//image[startSSL_49][何も入力せず［OK］をクリック][scale=0.6]{
//}

［空のパスフレーズを指定しています。空のままで処理を続行しますか？］と表示されますが、そのまま［OK］をクリックします。

//image[startSSL_50][［OK］をクリック][scale=0.6]{
//}

無事にSSHのキーペア（秘密鍵と公開鍵）が作成されて、［認証キーリスト］に［startSSLKey］が表示されました。［公開鍵］をクリックしてください。（@<img>{startSSL_51}）

//image[startSSL_51][［startSSLKey］が表示されたら［公開鍵］をクリック][scale=0.6]{
//}

公開鍵が表示されました。この後すぐに使いますので、［クリップボードにコピーされる公開鍵］で表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。公開鍵をメモしたら［OK］をクリックして閉じます。

//footnote[windowsComment][mochikoAsTech@の部分には、<Windowsのユーザ名>@が入ります]

//image[startSSL_52][表示された公開鍵（文字列）はまるごとコピーしてメモ帳にペーストしておこう][scale=0.6]{
//}

あとは［キャンセル］を繰り返しクリックして、起動中のRLoginは一旦閉じてしまって構いません。RLoginは、後でサーバへ入るときに使いますので、デスクトップの「rlogin_x64」フォルダと、その中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。メモ帳にメモした公開鍵も、消してしまわないようご注意ください。

=== Macでターミナルを準備する

Mac@<fn>{macTerminal}を使っている方は、最初から「ターミナル」（@<img>{mac02}）というソフトがインストールされていますのでそちらを利用しましょう。

//footnote[macTerminal][2020年2月以前にリリースされたmacOSを対象とします]

//image[mac02][最初からインストールされている「ターミナル」を使おう][scale=0.8]{
//}

ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索（@<img>{mac01}）すれば起動できます。

//image[mac01][どこにあるのか分からなかったらSpotlightで「ターミナル」と検索][scale=0.8]{
//}

=== MacでSSHのキーペア（秘密鍵・公開鍵）を作成する

ターミナルを起動したら、キーペアを作成します。Macを使っている方は、ターミナルで次のコマンドを実行してください。@<fn>{tilde}先頭の「$」を入力する必要はありません。

//footnote[tilde][@<code>{ssh-keygen}コマンドは名前のとおり、SSHの鍵（key）を生成（generate）するコマンドです。-fオプションでは、生成する鍵のファイル名を指定しています。~（チルダ）はホームディレクトリを表しますので、@<code>{-f ~/Desktop/startSSLKey}は「/Users/<ユーザ名>/Desktop」のフォルダの中に「startSSLKey」という名前の鍵を作って、という意味です。@<code>{-N ''}は空のパスフレーズを指定しています]

//cmd{
$ ssh-keygen -N '' -f ~/Desktop/startSSLKey
//}

次のように表示されたらキーペア（秘密鍵・公開鍵）の作成は完了です。

//cmd{
$ ssh-keygen -N '' -f ~/Desktop/startSSLKey
Generating public/private rsa key pair.
Your identification has been saved in /home/mochikoAsTech/Desktop/startSSLKey.
Your public key has been saved in /home/mochikoAsTech/Desktop/startSSLKey.pub.
The key fingerprint is:
a2:52:43:dd:70:5d:a8:4f:77:47:ca:f9:69:79:14:48 mochikoAsTech@mochikoMacBook-Air.local
The key's randomart image is:
+--[ RSA 2048]----+
|      . .. ooE.  |
|     . +  o  . ..|
|    . . ..   . +.|
|   .    . . . = o|
|    o . So . . +o|
|   . o .  .    +o|
|  . .         . .|
|   .             |
|                 |
+-----------------+
//}

作成した秘密鍵は、オーナー以外が使えないようchmodというコマンドで読み書き権限を厳しくしておきます。

//cmd{
$ chmod 600 ~/Desktop/startSSLKey
//}

ホームディレクトリに秘密鍵（startSSLKey）と、公開鍵（startSSLKey.pub）ができあがっているはずです。cat（キャット）コマンド@<fn>{cat}で公開鍵を表示してみましょう。

//footnote[cat][catは猫ではなく「conCATenate files and print on the standard output」の略です]

//cmd{
$ cat ~/startSSLKey.pub
ssh-rsa AAAAB3NzaC1yc2（中略）Unidb+6FjiLw== mochikoAsTech@mochikoMacBook-Air.local
//}

//footnote[macComment][mochikoAsTech@mochikoMacBook-Air.localの部分は、<Macのユーザ名>@<Macのホスト名>が入るので人によって異なります]

この後すぐに使いますので、表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。

以上で事前準備は完了です。お待たせしました。いよいよサーバを立てましょう。

===[column] 【コラム】SSHの秘密鍵にパスフレーズは設定すべき？

秘密鍵に［パスフレーズ］を設定しておくと、鍵を使ってSSHでサーバに入ろうとしたとき、「鍵を発動するにはパスフレーズを叫べ…！」という感じでパスフレーズを聞かれます。

つまり、もしあなたの秘密鍵が盗まれて誰かに勝手に使われそうになっても、パスフレーズを設定していれば鍵の悪用が防げます。スマホ本体が盗まれてしまっても、暗証番号が分からなければロック画面が解除できず、勝手に使えないのと同じです。

これは「あなたは何を持っているのか」「あなたは何を知っているのか」「あなたは誰なのか」という複数の要素の中から、2つを用いることで認証の強度を高める「二要素認証」と呼ばれる考え方です。「あなたは秘密鍵を持っている」「あなたはパスフレーズを知っている」という2つの要素を組み合わせることで、単要素での認証よりも強度が高まります。ちなみに「あなたは誰なのか」は指紋認証や顔認証ですね。

ですが「パスワード認証じゃなくて鍵認証なのに、やっぱりパスフレーズが必要なの…？」という具合に、初心者を混乱に陥れやすいので、本書では秘密鍵をパスフレーズなしで作って使用します。

パスフレーズは「設定していれば絶対に安心！」というものではありませんが、上記の理由から、本来であれば設定した方がいいものです。後で「やっぱり設定しておこう」と思ったら、一度作成した秘密鍵に対して、後からパスフレーズを設定することも可能です。なお手元の秘密鍵に、後からパスフレーズを設定しても、サーバ側での変更は特に必要ありません。

===[/column]

== コンピュートでサーバを立てる

それでは下準備ができたので、Oracle Cloudのコンソールに戻ってサーバを立てましょう。コンソールにサインインしたら、［VMインスタンスの作成］をクリック（@<img>{startSSL_46}）します。ちなみにOracle Cloudにはデータベース管理やストレージなど、さまざまなサービスがありますが、クラウドサーバや物理サーバなどの@<ttb>{サーバが立てられるサービスは「コンピュート」}と呼ばれています。そしてOracle Cloudでは@<ttb>{サーバのことをインスタンス}と呼びます。ここから先でインスタンスと書いてあったら「サーバのことだな」と思ってください。

//image[startSSL_46][［VMインスタンスの作成］をクリック][scale=0.8]{
//}

［コンピュート・インスタンスの作成］が表示されたら、［インスタンスの命名］に［startSSLInstance］と入力します。（@<img>{startSSL_54}）その下の［オペレーティング・システムまたはイメージ・ソースを選択します］は、何も変更せず［Oracle Linux 7.7］のままで構いません。

//image[startSSL_54][［インスタンスの命名］に［startSSLInstance］と入力][scale=0.8]{
//}

ところでこの［オペレーティング・システム］とはいったい何のことでしょうか？

=== OSはOracle Linux 7.7を使おう

パソコンにはOS（オペレーティング・システム）という基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

本書では、OSはデフォルトの［Oracle Linux 7.7］を使用します。Oracle LinuxならOracle Cloudのツールがあらかじめ入っていますので、Oracle Cloudでインスタンスを立てるときは@<ttb>{OSはOracle Linuxにする}ことをお勧めします。Oracle LinuxはRed Hat系のディストリビューションですので、RHELやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

2020年1月時点で、Oracle Linuxには次の2種類があります。

 * Oracle Linux 6.10
 * Oracle Linux 7.7

Oracle Linux 6.10はCentOS 6と同じRHEL6系、Oracle Linux 7.7はCentOS 7と同じRHEL7系なので、使い勝手もほぼ同じです。

=== 作っておいたSSHの公開鍵を設置しよう

さらに下にスクロールします。［SSHキーの追加］は、［SSHキーの貼付け］を選択します。先ほどメモ帳にメモしておいた公開鍵を［SSHキー］にペーストします。公開鍵は改行を含まず、先頭の「ssh-rsa」から末尾の「<ユーザ名>@<ホスト名>」のようなコメントまで、まるごと1行です。（@<img>{startSSL_55}）

//image[startSSL_55][［SSHキーの貼付け］を選択してメモしておいた公開鍵をペースト][scale=0.8]{
//}

公開鍵をペーストしたら［作成］をクリックします。

=== 〈トラブル〉"Out of host capacity."が起きたらどうすればいい？

さて、元気よく［作成］をクリックしたのに、真っ赤な［Out of host capacity.］が表示されてしまった…という方が一定数いらっしゃると思います。大丈夫、あなたは悪くありません。いま理由を説明するので落ち着いてください。「そんなの表示されなかったよ？」という方は、この〈トラブル〉は読み飛ばして、この先の「3.2.5 サーバが起動するまで待とう」までジャンプしてください。

//image[startSSL_56]["Out of host capacity."と表示されて何も起きない！][scale=0.8]{
//}

"Out of host capacity."は、直訳すると「ホスト容量が不足しています」という意味ですが、ホストってなんでしょう？

あなたがいまOracle Cloudで立てようとしたインスタンスは、家でいうと「一軒家」ではなく、マンションの101号室や403号室のような「各部屋」にあたります。このときマンションの建物をホストサーバ、各部屋をゲストサーバと呼びます。

//image[houseAndMansion][マンションの建物をホストサーバ、各部屋をゲストサーバと呼ぶ][scale=0.8]{
//}

「ホストの容量が不足している」ということは…つまり、あなたがOracle Cloudの無料マンションに入居しようとしたら、「ごめんね、無料マンションは大人気でいま空き部屋がないの」と断られてしまった、という状況なのです。

Oracle CloudのAlways Freeは有効期限なしでずっと無料で使える、とても魅力的なサービスです。そのためOracle Cloud側も定期的に新築マンションを追加しているものの、頻繁にリソース不足に陥ってはこういう状況になるようです。

この"Out of host capacity."が発生してしまった場合、次のどちらかが起きてホストの容量不足が解消しない限り、Always Freeの枠でインスタンスは立てられません。

 * 自分以外のユーザがインスタンスを解約してリソースを開放する
 * Oracle Cloudがリソースを増やす
 
ですが、Always Freeとは別に、我々には30日間だけ有効な$300の無償クレジットが与えられています。たとえ無料マンションが満室でも、有料マンションなら空きがあります。30日経ったら消えてしまう$300のお小遣いを握りしめて、次の方法で有料マンションのお部屋を借りにいきましょう！

=== Always Freeではなく無償クレジットの枠でサーバを立てよう

次の手順は、@<ttb>{"Out of host capacity."が表示された人だけ}実施してください。

"Out of host capacity."を回避するため、少し上にスクロールして［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリック（@<img>{startSSL_57}）しましょう。もともと選択していたのは［Always Free対象］のマークが付いた［VM.Standard.E2.1.Micro (仮想マシン)］という種類のインスタンスでした。

//image[startSSL_57][［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリック][scale=0.8]{
//}

Oracle Cloudでは、マシンスペックごとに「シェイプ」という区分@<fn>{whatIsShape}があります。インスタンスのシェイプを、いま選択されている［VM.Standard.E2.1.Micro］から変更するため、［シェイプの変更］をクリックしてください。

//footnote[whatIsShape][AWSのインスタンスタイプと同じものだと思ってください]

//image[startSSL_58][［シェイプの変更］をクリック][scale=0.8]{
//}

OCPU@<fn>{ocpu}が2、メモリが16GBの［VM.Standard.E2.2］@<fn>{shapeName}にチェックを入れて、［シェイプの選択］をクリックしましょう。

//footnote[ocpu][OCPUはOracle Compute Unitsの略で、ごく簡単に言うとCPUコア数の単位です。OCPU1つは、vCPU（仮想CPU）2つに相当しますので、もし「AWSのEC2でvCPUが4のインスタンスを使っている。同等スペックのインスタンスを用意してほしい」と頼まれたら、Oracle CloudではOCPUが2のシェイプを選べば大丈夫です。ただしCPUの単純比較だけではなく、他にもメモリやストレージなど、必要なスペックを考えて適したシェイプを選ぶようにしましょう]

//footnote[shapeName][シェイプの名前は、まず接頭辞が「VM」なら仮想サーバ（Virtual Machine）、「BM」なら物理サーバ（Bare Metal）を表しています。その後ろの単語は「Standard」（汎用）や「DenseIO」（高密度I/O）といった特徴、3番目の「E2」や「2」はシェイプの世代、最後の「2」や「8」はOCPUの数を表しています]

//image[startSSL_59][「VM.Standard.E2.2」に変更して［シェイプの選択］をクリック][scale=0.8]{
//}

それ以外は何も変更せずに、いちばん下の［作成］をクリックします。

//image[startSSL_60][［作成］をクリック][scale=0.8]{
//}

=== サーバが起動するまで待とう

オレンジ色で［プロビジョニング中...］と表示（@<img>{startSSL_61}）されたら、サーバが起動するまでそのまま数分待ちましょう。

//image[startSSL_61][［プロビジョニング中...］と表示されたら数分待つ][scale=0.8]{
//}

サーバが起動すると、表示が緑色の［実行中］に変わります（@<img>{startSSL_62}）。おめでとうございます。サーバが立てられました！

//image[startSSL_62][［実行中］に変わった！サーバが立った！][scale=0.8]{
//}

===[column] 【コラム】Oracle Cloudのコンピュートの金額計算方法

ところで、「VM.Standard.E2.2」というシェイプのインスタンスをまるまる1ヶ月使ったら、一体いくら分になるのでしょう？うっかり$300を超えてしまわないか、ちょっと心配なので計算してみましょう。

コンピュートの価格表@<fn>{pricing}を見てみると、［Compute - Standard - E2］は［$0.03］@<fn>{ocpuNow}と書いてあります。これは［Pay as You Go (OCPU Per Hour)］と書いてあるとおり、1OCPUごとに1時間あたりかかる金額です。@<fn>{awsRegion}

「VM.Standard.E2.2」はOCPUが2なので、$0.03*2で1時間あたり$0.06かかることが分かります。1ヶ月を744時間（24時間*31日）として、$0.06*744時間で$44.64です。つまり「VM.Standard.E2.2」を1台立てたくらいでは、$300の無償クレジットを使い切ることはないので安心しましょう。ちなみにOracle Cloudでは$1は120円換算@<fn>{rate}なので、$44.64は日本円だと5356.8円ですね。

===[/column]

//footnote[pricing][@<href>{https://www.oracle.com/jp/cloud/compute/pricing.html}]
//footnote[ocpuNow][2020年2月時点の金額]
//footnote[awsRegion][ちなみにAWSは、同スペックのインスタンスでもリージョンごとに価格が異なりますが、Oracle Cloudはどこのリージョンでも同一の価格です]
//footnote[rate][2020年2月時点のレート]

===[column] 【コラム】Oracle CloudとAWSはどっちが安い？

Oracle Cloudは他のクラウドに比べて価格が安いのが特徴のひとつです。どれくらい安いのか、Oracle CloudとAWSでサーバの価格を比較してみましょう。

例えば同スペックのVM.Standard.E2.1（Oracle Cloud）とm5a.large（AWS）を比較すると、Oracle Cloudの価格はAWSの3分の1以下になります。（@<table>{oracleAwsDiff}）

//table[oracleAwsDiff][Oracle CloudとAWSの価格比較]{
　	Oracle Cloud	AWS
------------------------------------
インスタンスの種類	VM.Standard.E2.1	m5a.large
CPU	OCPU:1（vCPU:2相当）	vCPU:2
メモリ	8GB	8GB
1時間あたり	$0.03	$0.112
月額	2678.4円	9999.36円
//}

シェアトップを独走するAWSに対して、後発のクラウドは勝つためにコスト面や性能面でそれぞれ大きなメリットを打ち出してきています。AWSが最適なのであればAWSを選択すべきですが、「みんなが使っているから」というだけの理由で、あまり深く考えずにAWSを使っているのであれば、他のクラウドにも目を向けてみることをお勧めします。

===[/column]

=== 接続先サーバのIPアドレス

無事にサーバが立ち上がったら、IPアドレスを確認しておきましょう。

先ほど作成したインスタンスの［startSSLInstance］で、［プライマリVNIC情報］（@<img>{instancePublicIPAddress}）にある［パブリックIPアドレス］をメモ（@<table>{IPv4Address}）してください。

//image[instancePublicIPAddress][［プライマリVNIC情報］の［パブリックIPアドレス］をメモしておこう][scale=0.8]{
//}

//table[IPv4Address][インスタンスの［パブリックIPアドレス］]{
例	パブリックIPアドレス
------------------------------------
140.238.33.51	
//}

それではメモしたIPアドレスを使ってサーバにログインしてみましょう。

== サーバにSSHでログインしよう

立てたばかりのサーバに、ターミナルを使ってSSHでログインします。Windows、Macの順番で手順を説明します。

=== WindowsのRLoginを使ってサーバにログインしよう

Windowsのパソコンを使っている方は、RLoginを起動（@<img>{startRLogin02}）してください。起動したら［新規］をクリックします。

//image[startRLogin02][RLoginが起動したら［新規］をクリック][scale=0.5]{
//}

まずは［エントリー（上）］に［startSSLInstance］と入力します。［コメント（下）］は入力しなくて構いません。続いて［ホスト名（サーバーIPアドレス）］に、先ほどメモした［パブリックIPアドレス］を入力（@<img>{startRLogin03}）します。［ログインユーザー名］には［opc］と入力してください。opcというのはOracle Linuxのインスタンスを作成すると、最初から存在しているデフォルトユーザです。

//image[startRLogin03][［ホスト名（サーバーIPアドレス）］と［ログインユーザー名］を入力][scale=0.5]{
//}

次に左メニューで［プロトコル］を選択（@<img>{startRLogin04}）したら、［KeepAliveパケットの送信間隔(sec)］にチェックを入れておきます。チェックを入れておくと、ターミナルをしばらく放っておいても接続が勝手に切れません。続いて［認証キー］をクリックします。

//image[startRLogin04][チェックを入れて［認証キー］をクリック][scale=0.6]{
//}

［認証キー］リストで［startSSLKey］にチェックが入っていることを確認（@<img>{startRLogin05}）します。このリストはログイン時に使用する鍵のリストです。キーケースに自宅と実家の鍵をぶらさげておくように、複数の鍵をリストに入れておくことも可能です。チェックが入っていたら［OK］をクリックして閉じましょう。

//image[startRLogin05][［startSSLKey］にチェックが入っていることを確認][scale=0.6]{
//}

続いて左メニューで［クリップボード］を選択（@<img>{startRLogin06}）したら、［左クリックの範囲指定だけでクリップボードにコピーする］と［コピー時に範囲指定を解除しない］にチェックを入れて［右クリックでペースト］を選択します。

//image[startRLogin06][右クリックや左クリックの設定][scale=0.6]{
//}

次に左メニューで［フォント］を選択（@<img>{startRLogin07}）したら、文字セットを［UTF-8］に変更します。すべて設定できたら［OK］をクリックしてください。

//image[startRLogin07][文字セットを［UTF-8］に変更][scale=0.6]{
//}

これで設定が保存できました。今やった設定は最初の1回のみで、2回目以降は不要です。それでは［OK］をクリック（@<img>{startRLogin08}）して、サーバにログインしましょう。

//image[startRLogin08][設定が保存できたので［OK］をクリックしてサーバにログイン][scale=0.6]{
//}

すると初回のみ、この［公開鍵の確認］が表示（@<img>{startRLogin09}）されますので、［接続する］をクリック@<fn>{first}します。下部の［この公開鍵を信頼するリストに保存する］にチェックが入っていると、RLoginがサーバ固有のフィンガープリント@<fn>{fingerprint}を覚えてくれます。そして次回以降は「これはこのサーバで過去に信頼した公開鍵と同じだ」と判断して、RLoginがそのままサーバへ接続させてくれます。

//footnote[first][今後、別のパソコンから同じサーバへ接続する際には、元のパソコンに保存されているサーバのフィンガープリントと、初回接続時に表示されるフィンガープリントを比較することで、DNSキャッシュポイズニングなどの攻撃によって、他のサーバに誘導されていないか確認できます]
//footnote[fingerprint][公開鍵のハッシュ値のことをフィンガープリント（指紋）と呼びます]

//image[startRLogin09][［公開鍵の確認］が表示されたら［接続する］をクリック][scale=0.4]{
//}

続いて［信頼するホスト鍵のリストを更新しますか？］と聞かれたら［はい］をクリック（@<img>{startRLogin10}）してください。

//image[startRLogin10][［信頼するホスト鍵のリストを更新しますか？］と表示されたら［はい］をクリック][scale=0.4]{
//}

［opc@startsslinstance］と表示（@<img>{startRLogin11}）されたら無事サーバにログインできています。自分でサーバを立てて、SSHでのログインすることができましたね。おめでとうございます！

//image[startRLogin11][［opc@startsslinstance］と表示されたら成功！][scale=0.8]{
//}

=== 〈トラブル〉サーバにログインできない！

もし［opc@startsslinstance］と表示されず、代わりに［SSH2 User Auth Failure "publickey,gssapi-keyex,gssapi-with-mic" Status=1004 Send Disconnect Message... gssapi-with-mic」というようなエラーメッセージが表示（@<img>{startRLogin12}）されてしまったら、これは「鍵がない人は入れないよ！」とお断りされている状態です。［認証キー］リストで［startSSLKey］にチェックが入っていないか、あるいは誤って別の秘密鍵を選択しているものと思われますので、［認証キー］の設定を確認してみてください。

//image[startRLogin12][このエラーが表示されたら［認証キー］を確認しよう][scale=0.4]{
//}

［接続済みの呼び出し先が一定の時間を過ぎても正しく応答しなかったため、接続できませんでした。］というエラーメッセージが表示（@<img>{startRLogin13}）されてしまった場合は、［ホスト名（サーバーIPアドレス）］に書いた［パブリックIPアドレス］が間違っているものと思われます。［ホスト名（サーバーIPアドレス）］のIPアドレスを確認してみてください。

//image[startRLogin13][このエラーが表示されたら［ホスト名（サーバーIPアドレス）］のIPアドレスを確認しよう][scale=0.4]{
//}

=== Macのターミナルを使ってサーバにログインしよう

Macを使っている方は、ターミナル（@<img>{mac04}）を起動してください。

//image[mac04][「ターミナル」を起動しよう][scale=0.8]{
//}

起動したターミナルで次の文字を入力したらReturnキーを押します。「パブリックIPアドレス」の部分は先ほどメモした［パブリックIPアドレス］に書き換えてください。-iオプションは「サーバにはこの鍵を使って入ります」という意味です。「startSSLKey」を保存した場所がデスクトップ以外だった場合はこちらも適宜書き換えてください。

//cmd{
$ ssh opc@パブリックIPアドレス -i ~/Desktop/startSSLKey
//}

初回のみ次のようなメッセージが表示されますが、「yes」と打ってReturnキー@<fn>{mitmMac}を押してください。

//footnote[mitmMac][yesと打った理由は、P62の注釈で説明しています]

//cmd{
Are you sure you want to continue connecting (yes/no)?
//}

［opc@startsslinstance］と表示されたら、SSHでサーバにログインできています。おめでとうございます！今後は、いまやったのと同じやり方をそのまま繰り返せば、サーバにログインできます。

== NGINXをインストールしよう

それではサーバにログインできたので、必要なミドルウェアをインストールしていきましょう。最初にrootになっておいてください@<fn>{prompt}。

//footnote[prompt][以降は、例として書いてある部分のプロンプトが、「$」だったらopcのような一般ユーザでコマンドを実行、「#」だったらrootでコマンドを実行してください。例に「$」や「#」が書いてあっても、ターミナルで「$」や「#」を自分で入力する必要はありません]

//cmd{
$ sudo su -
//}

インストールするときはyum（ヤム）というコマンドを使います。先ずはyumで色々アップデートしておきましょう。Windowsアップデートみたいなものです。

//cmd{
# yum update -y
//}

画面にたくさん文字が流れて、少し時間がかかりますが、最後に［Complete!］と表示（@<img>{startSSL_66}）されたら問題なく完了しています。ちなみに-yオプションはYESを意味するオプションです。-yオプションをつけないで実行すると「これとこれをアップデートするけどいい？ダウンロードサイズとインストールサイズはこれくらいだよ」という確認が表示され、yと入力してEnterキーを押さないとアップデートされません。

//image[startSSL_66][最後に［Complete!］と表示されたらアップデートは完了][scale=0.8]{
//}

続いてウェブサーバのNGINX@<fn>{nginxPronounce}をインストールします。2020年1月現在の安定バージョン@<fn>{version}である1.16系をインストールしたいので、yumのリポジトリ（どこからNGINXをダウンロードしてくるか）にNGINX公式を追加しましょう。

//footnote[nginxPronounce][NGINXと書いて「えんじんえっくす」と読みます。ウェブサーバのミドルウェアの中でNGINXは順調にシェアを伸ばし、2019年4月にとうとうApacheを抜いてシェア1位になりました。@<href>{https://news.mynavi.jp/article/20190424-813722/}]

//cmd{
# rpm -ivh http://nginx.org/packages/centos/7/noarch/RPMS/nginx-release-centos
-7-0.el7.ngx.noarch.rpm　←実際は改行なしで1行
# cat /etc/yum.repos.d/nginx.repo 

↓以下が表示されればOK
# nginx.repo

[nginx]
name=nginx repo
baseurl=http://nginx.org/packages/centos/7/$basearch/
gpgcheck=0
enabled=1
//}

//footnote[version][サーバに入っているNGINXのバージョンがいくつなのか？という情報は大切です。今後、あなたがNGINXの設定ファイルを書こうと思って調べたとき、例えば1.12系の設定方法を参考にしてしまうと、1.16系のNGINXの環境では上手く動かない可能性があります。]

yumでNGINXをインストールします。

//cmd{
# yum install -y nginx
//}

［Complete!］と表示されたらインストール完了です。バージョン情報を表示することで、ちゃんとインストールされたか確認してみましょう。

//cmd{
# nginx -v
nginx version: nginx/1.16.1　←バージョン情報が表示されればインストールできている
//}

ちょっと分かりにくいかも知れませんが、パソコンにMicrosoft Excelをインストールしたら「表計算というサービスが提供できるパソコン」になるのと同じで、サーバにこのNGINXをインストールすると「リクエストに対してウェブページを返すサービスが提供できるサーバ」、つまりウェブサーバになります。 今回はNGINXを入れましたが、ウェブサーバのミドルウェアは、Apacheをはじめとして他にも色々な種類があります。

インストールが終わったので、サーバを再起動した場合もNGINXが自動で立ち上がってくるよう、自動起動の設定もオンにしておきましょう。systemctlコマンド@<fn>{systemctlCommand}で、NGINXの自動起動を有効（enable）にします。

//footnote[systemctlCommand][自動起動の設定は、CentOS 6系だとchkconfigコマンドで行なっていましたが、7系ではsystemctlコマンドになっています]

//cmd{
# systemctl enable nginx
# systemctl is-enabled nginx
enabled　←有効になったことを確認
//}

== FirewalldでHTTPとHTTPSを許可しよう

続いてサーバの中で動いているファイアウォールの設定を変更します。まずは現状、何がファイアウォールを通れるようになっているのか確認@<fn>{firewalld}してみましょう。

//cmd{
# firewall-cmd --list-services
dhcpv6-client ssh
//}

//footnote[firewalld][Oracle Linux 7、及びOracle CloudのCentOS 7ではfirewalldがデフォルトで有効化されています。 @<href>{https://docs.oracle.com/cd/E77565_01/E54670/html/ol7-firewalld-cfg.html}]

dhcpv6-clientとsshは通っていいけれど、それ以外は誰であろうと通さないぞ！という設定になっています。このままではブラウザでサイトを見ようとしても、ウェブページを返してくれるはずのNGINXまで、HTTPやHTTPSのリクエストが届きません。そこで次のように、許可対象にhttpとhttpsを追加します。追加したら、変更が反映されるようリロードしてください。それぞれ［success］と表示されたら成功しています。

//cmd{
# firewall-cmd --add-service=http --permanent
success

# firewall-cmd --add-service=https --permanent
success

# firewall-cmd --reload
success
//}

これでファイアウォールの設定が変更できたので、もう一度、ファイアウォールの設定を確認してみましょう。ファイアウォールを通っていい対象に、httpとhttpsが追加されていれば問題ありません。

//cmd{
# firewall-cmd --list-services
dhcpv6-client http https ssh
//}

これで、HTTPでサイトを見るためのウェブサーバの設定はおしまいです。

== なぜかHTTPでサイトが見られない

ウェブサーバも立てたし、サーバの中のファイアウォールに穴も空けました。これで準備完了！サーバを立てたときにメモした［パブリックIPアドレス］をコピーしたら、ブラウザのアドレスバーにペーストして、サイトを開いてみましょう。

するとしばらくぐるぐるした後で、［接続がタイムアウトしました］と表示されてしまいました。（@<img>{startSSL_77}）

//image[startSSL_77][なぜかHTTPでサイトが表示されない…][scale=0.8]{
//}

403や404、あるいは502などのステータスコードも返ってきていないので、そもそもNGINXまでたどり着けていないようです。

=== サーバの手前にあるファイアウォールにも穴を空けよう

先ほどサーバの中にあるファイアウォールの設定を変更して、HTTPとHTTPSが通れるようにしましたが、実はサーバの中だけでなく、サーバに辿り着く手前にも、もう1つファイアウォールがいます。サイトが表示されなかったのは、「ウェブページを見せて！」というリクエストが、@<ttb>{サーバの手前のファイアウォールで阻まれていた}ためなのです。サーバの手前にあるファイアウォールにも穴を空けて、HTTPとHTTPSがサーバまでたどり着けるようにしましょう。

再びOracle Cloudのコンソールに戻って、左上の［ハンバーガーメニュー］から［コンピュート］の［インスタンス］を開きます。（@<img>{startSSL_68}）

//image[startSSL_68][［ハンバーガーメニュー］から［コンピュート］の［インスタンス］を開く][scale=0.8]{
//}

インスタンスの一覧が表示されるので［startSSLInstance］をクリックします。（@<img>{startSSL_69}）

//image[startSSL_69][［startSSLInstance］をクリック][scale=0.8]{
//}

［パブリック・サブネット］をクリックします。（@<img>{startSSL_70}）

//image[startSSL_70][［パブリック・サブネット］をクリック][scale=0.8]{
//}

もう一度、［パブリック・サブネット］をクリックします。（@<img>{startSSL_71}）

//image[startSSL_71][もう一度、［パブリック・サブネット］をクリック][scale=0.8]{
//}

［セキュリティ・リスト］の中にある［Default Security List for VirtualCloudNetwork～］をクリック（@<img>{startSSL_72}）します。この［セキュリティ・リスト］が、サーバの手前にいるファイアウォールです。

//image[startSSL_72][［Default Security List for VirtualCloudNetwork～］をクリック][scale=0.8]{
//}

［イングレス・ルール］で、［イングレス・ルールの追加］をクリック（@<img>{startSSL_73}）します。

//image[startSSL_73][［イングレス・ルールの追加］をクリック][scale=0.8]{
//}

［ソースCIDR］に［0.0.0.0/0］@<fn>{allowFromAll}を入力します。［宛先ポート範囲］には［80,443］@<fn>{portNumber}を入力します。（@<img>{startSSL_74}）どちらも入力できたら、［イングレス・ルールの追加］をクリックします。

//footnote[allowFromAll][ソースCIDRは接続元のIPアドレス範囲のことで、0.0.0.0/0はすべてのIPアドレスを指します。つまり接続元がどんなIPアドレスでもファイアウォールを通します、ということですね]
//footnote[portNumber][ポート番号とは、サーバという家や、その手前のファイアウォールという壁についているドアの番号のようなものだと思ってください。同じサーバを訪問するときでもSSHは22番のドアを、HTTPは80番のドアを、HTTPSは443番のドアを通ります]

//image[startSSL_74][［ソースCIDR］に［0.0.0.0/0］、［宛先ポート範囲］には［80,443］を入力][scale=0.8]{
//}

［イングレス・ルール］に、HTTP（80番ポート）とHTTPS（443番ポート）へのリクエストを通す設定が追加されました。（@<img>{startSSL_75}）

//image[startSSL_75][ルールが追加された！][scale=0.8]{
//}

=== 今度こそHTTPでサイトを見てみよう

再び、サーバを立てたときにメモした［パブリックIPアドレス］を、ブラウザで開いてみましょう。（@<img>{startSSL_76}）

//image[startSSL_76][今度こそHTTPでサイトが見られた！][scale=0.8]{
//}

［Welcome to nginx!］と表示されました！これでまず、「HTTPでサイトを表示する」はクリアできました。

== ドメイン名の設定をしよう

ウェブサーバを立てて、HTTPでサイトを表示できたので、続いては@<ttb>{HTTPSのサイト用にドメイン名を用意}します。「自分のドメイン名？そんなの持ってないよ！」という方は、先に「DNSをはじめよう」@<fn>{boothDNS}を読んで、ドメイン名を買ってからこの先へ進むようにしてください。@<fn>{ipSsl}

//footnote[boothDNS][@<href>{https://mochikoastech.booth.pm/items/881622}]
//footnote[ipSsl][本書で使用するFujiSSLのSSL証明書は、グローバルIPアドレスに対しては発行できないため、必ずドメイン名が必要です。 @<href>{https://www.fujissl.jp/faq/review/1095/}]

それでは、あなたのドメイン名で「ssl.自分のドメイン名」というAレコードを作成し、サーバの［パブリックIPアドレス］と紐付けてください。ネームサーバはお名前.comを使用してもいいですし、AWSのRoute53で設定しても構いません。

なお筆者が「DNSをはじめよう」で購入したのは@<code>{startdns.fun}というドメイン名だったので、@<code>{ssl.startdns.fun}というAレコードを作って、さっき立てたばかりのサーバの［パブリックIPアドレス］と紐付けます。例えばネームサーバが「お名前.com」なら、DNS設定の画面でこのようにAレコードを追加します。（@<img>{onamaeARR}）

//image[onamaeARR][「ssl.自分のドメイン名」のAレコードを作成する][scale=0.6]{
//}

Aレコードを追加できたかどうかは、次のdigコマンドで確認できます。digコマンドをたたいた結果、サーバのIPアドレスが返ってくればAレコードは設定できています。

//cmd{
$ dig ssl.自分のドメイン名 a +short
//}

筆者の場合は、次のように表示されました。

//cmd{
$ dig ssl.startdns.fun a +short
140.238.33.51
//}

ドメイン名が設定できたら、ブラウザでも「@<code>{http://ssl.自分のドメイン名}」をたたいてみましょう。先ほどと同じNGINXのページが表示されるはずです。（@<img>{startSSL_78}）

//image[startSSL_78][「ssl.自分のドメイン名」でHTTPのサイトが表示された！][scale=0.8]{
//}

HTTPでサイトを見ることができましたね。では同じドメイン名をHTTPSで開いてみるとどうでしょう？ブラウザで「@<code>{https://ssl.自分のドメイン名}」を開いてみると、［正常に接続できませんでした］と表示（@<img>{startSSL_85}）されました。

//image[startSSL_85][HTTPSで開くと［正常に接続できませんでした］と表示された][scale=0.8]{
//}

なぜなら、NGINXでHTTPの設定はしたけれど、HTTPSの設定はまだだからです。それではHTTPSでもサイトが見られるように、次章でSSL証明書を取得して、設定を進めていきましょう。
