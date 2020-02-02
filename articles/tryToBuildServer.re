= Oracle Cloudでサーバを立てよう

この章では実際にOracle Cloudでサーバを立てます。

インフラエンジニアのお仕事体験みたいできっと楽しいですよ！

//pagebreak

== 事前準備

=== お使いのパソコンがWindowsの場合

==== RLoginのインストール

Windowsのパソコンを使っている方は、サーバを立てる前に「ターミナル」と呼ばれる黒い画面のソフトをインストールしておきましょう。サーバに接続するときにはこのターミナルを使うのですが、ターミナルのソフトには色々な種類があります。

 * RLogin（@<href>{http://nanno.dip.jp/softlib/man/rlogin/}）
 * Poderosa（@<href>{https://ja.poderosa-terminal.com/}）
 * Tera Term（@<href>{https://ja.osdn.net/projects/ttssh2/}）
 * PuTTYjp（@<href>{http://hp.vector.co.jp/authors/VA024651/PuTTYkj.html}）

//image[rlogin][RLogin][scale=0.8]{
//}

本著ではいちばん上のRLogin（@<img>{rlogin}）を使って説明していきますので、特にこだわりがなければRLoginを使うことをお勧めします。RLoginの「実行プログラム(64bit)@<fn>{64bit}」（@<img>{downloadRLogin01}）のURL、@<href>{http://nanno.dip.jp/softlib/program/rlogin_x64.zip}をクリックしてください。

//footnote[64bit][もしパソコンのWindowsが32bit版だった場合は「実行プログラム(32bit)」のURLをクリックしてください。]

//image[downloadRLogin01][「実行プログラム(64bit)」のURLをクリックしてダウンロード][scale=0.6]{
//}

ダウンロードしたZIPファイルを保存（@<img>{downloadRLogin02}）します。保存場所はどこでも構いませんが、後でどこに置いたか分からなくなりそうな人はデスクトップに保存しておきましょう。

//image[downloadRLogin02][「ファイルを保存する」でパソコンに保存][scale=0.6]{
//}

デスクトップのZIPファイル（rlogin_x64.zip）を右クリック（@<img>{downloadRLogin03}）して、［解凍＞デスクトップに解凍］@<fn>{lhaplus}をクリックします。

//image[downloadRLogin03][ZIPファイルを右クリックして解凍＞デスクトップに解凍][scale=0.6]{
//}

//footnote[lhaplus][ZIPファイルを右クリックしても「解凍」が見当たらないときは、圧縮・解凍の定番ソフトであるLhaplusをインストールしましょう。 @<href>{https://forest.watch.impress.co.jp/library/software/lhaplus/}]

解凍したら、デスクトップにできた「rlogin_x64」というフォルダの中にある「RLogin.exe」@<fn>{filenameExtension}（@<img>{downloadRLogin04}）をダブルクリックすればRLoginが起動（@<img>{downloadRLogin05}）します。

//footnote[filenameExtension][フォルダの中にRLoginはあるけどRLogin.exeなんて見当たらない…という場合、ファイルの拡張子が非表示になっています。この後も拡張子を含めてファイル名を確認する場面が何度かでてきますので、表示されていない人は「拡張子 表示」でGoogle検索して、拡張子が表示されるように設定変更しておきましょう。]

//image[downloadRLogin04][RLogin.exeをダブルクリック][scale=0.4]{
//}

//image[downloadRLogin05][RLoginが起動した][scale=0.6]{
//}

これでRLoginのインストールは完了です。

==== WindowsでSSHのキーペア（秘密鍵・公開鍵）を作成する

Windowsの方は、続いて起動したRLoginで［新規(N)］をクリックします。

//image[startSSL_45][［新規(N)］をクリック][scale=0.6]{
//}

左メニューの［プロトコル］を選択して、［認証キー(K)］をクリックします。

//image[startSSL_47][［プロトコル］を選択して［認証キー(K)］をクリック][scale=0.6]{
//}

［任意の名前が指定できます］に［startSSLKey］を入力して、［作成］をクリックします。

//image[startSSL_48][［startSSLKey］を入力して［作成］をクリック][scale=0.6]{
//}

［パスフレーズ］と［パス再入力］には何も入力せず、［OK］をクリックします。@<fn>{whatIsPassPhrase}

//footnote[whatIsPassPhrase][「p@$sw0rd」や「@dm1ni$trat0r」のように、ひとつの単語でできているのがパスワードです。それに対して「This 1s P@s$ Phrase.」のように空白を挟んだ文章（フレーズ）で構成されているのがパスフレーズです]

//image[startSSL_49][何も入力せず［OK］をクリック][scale=0.6]{
//}

［空のパスフレーズを指定しています。空のままで処理を続行しますか？］と表示されますが、そのまま［OK］をクリックします。

//image[startSSL_50][［OK］をクリック][scale=0.6]{
//}

［認証キーリスト］に、今作った［startSSLKey］が表示されたら、キーペア（秘密鍵・公開鍵）が無事できています。［公開鍵］をクリックしてください。（@<img>{downloadRLogin04}）

//image[startSSL_51][［startSSLKey］が表示されたら［公開鍵］をクリック][scale=0.6]{
//}

この後すぐに使いますので、［クリップボードにコピーされる公開鍵］で表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。公開鍵をメモしたら［OK］をクリックして閉じます。

//footnote[windowsComment][mochikoAsTech@の部分には、<Windowsのユーザ名>@が入ります]

//image[startSSL_52][表示された公開鍵（文字列）はまるごとコピーしてメモ帳にペーストしておこう][scale=0.8]{
//}

あとは［キャンセル］を繰り返しクリックして、起動中のRLoginはいったん閉じてしまって構いません。RLoginは、後でサーバへ入るときに使いますので、デスクトップの「rlogin_x64」フォルダと、その中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。メモした公開鍵も無くさないようご注意ください。

===[column] 【コラム】パスフレーズは設定すべき？しなくてもいい？

秘密鍵に［パスフレーズ］を設定しておくと、鍵を使ってサーバに入ろうとしたとき、「鍵を発動するにはパスフレーズを叫べ…！」という感じでパスフレーズを聞かれます。

つまり、もしあなたの秘密鍵が盗まれて誰かに勝手に使われそうになっても、パスフレーズを設定していれば鍵の悪用が防げます。スマホ本体が盗まれてしまっても、パスワードが分からなければロック画面が解除できず、勝手に使えないのと同じです。

ただ「パスワード認証じゃなくて鍵認証なのに、やっぱりパスフレーズが要るの…？」という具合に、初心者を混乱に陥れやすいので、本著では秘密鍵をパスフレーズなしで作って使います。

パスフレーズは「設定していれば絶対に安心！」というものではありませんが、上記の理由から、本来であれば設定した方がいいものです。後で「やっぱり設定しておこう」と思ったら、一度作成した秘密鍵に後からパスフレーズを設定することも可能ですよ。

===[/column]

=== お使いのパソコンがMacの場合

Macを使っている方は、最初から「ターミナル」（@<img>{mac02}）というソフトがインストールされていますのでそちらを利用しましょう。

//image[mac02][最初からインストールされている「ターミナル」を使おう][scale=0.8]{
//}

ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索（@<img>{mac01}）すれば起動できます。

//image[mac01][どこにあるのか分からなかったらSpotlightで「ターミナル」と検索][scale=0.8]{
//}

==== MacでSSHのキーペア（秘密鍵・公開鍵）を作成する

Macの方は、ターミナルで次のコマンドを実行してください。@<fn>{tilde}

//footnote[tilde][@<code>{ssh-keygen}コマンドは名前のとおり、SSHの鍵（key）を生成（generate）するコマンドです。-fオプションでは、生成する鍵のファイル名を指定しています。~（チルダ）はホームディレクトリを表しますので、@<code>{-f ~/Desktop/startSSLKey}は「/Users/<ユーザ名>/Desktop」のフォルダの中に「startSSLKey」という名前の鍵を作って、という意味です]

//cmd{
ssh-keygen -f ~/Desktop/startSSLKey
//}

すると次のように、パスフレーズの入力待ち状態になります。何も入力せずに、2回Enterを押してください。

//cmd{
$ ssh-keygen -f ~/Desktop/startSSLKey
Generating public/private rsa key pair.
Enter passphrase (empty for no passphrase): 　←何も入力せずにEnter
Enter same passphrase again: 　←何も入力せずにEnter
//}

次のように表示されたらキーペア（秘密鍵・公開鍵）の作成は完了です。

//cmd{
$ ssh-keygen -f ~/Desktop/startSSLKey
Generating public/private rsa key pair.
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/mochikoAsTech/Desktop/startSSLKey.
Your public key has been saved in /home/mochikoAsTech/Desktop/startSSLKey.pub.
The key fingerprint is:
a2:52:43:dd:70:5d:a8:4f:77:47:ca:f9:69:79:14:48 mochikoAsTech@ghana
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

ホームディレクトリに秘密鍵（startSSLKey）と、公開鍵（startSSLKey.pub）ができあがっているはずです。cat（キャット）コマンド@<fn>{cat}で公開鍵を表示してみましょう。

//footnote[cat][catは猫ではなく「conCATenate files and print on the standard output」の略です]

//cmd{
$ cat ~/startSSLKey.pub
ssh-rsa AAAAB3NzaC1yc2（中略）Unidb+6FjiLw== mochikoAsTech@mochikoMacBook-Air.local
//}

//footnote[macComment][mochikoAsTech@mochikoMacBook-Air.localの部分は、<Macのユーザ名>@<Macのホスト名>が入るので人によって異なります]

この後すぐに使いますので、表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。

以上で事前準備は完了です。お待たせしました。いよいよサーバを立てましょう。

===[column] 【コラム】ターミナルでコピー＆ペーストするには？

ターミナルで表示されている内容をコピーしたいときは、コピーしたい部分を@<ttb>{マウスで選択するだけ}です。（@<img>{startSSL_53}）選択してからCtrl+cを押す必要はありません。

//image[startSSL_53][マウスで選択するだけでコピーできる][scale=0.8]{
//}

逆にコピーした内容をターミナルへペーストしたいときはターミナル上で@<ttb>{右クリックするだけ}です。ターミナルのソフトにもよりますが、基本的にCtrl+pは使えないので注意してください。

===[/column]

== コンピュートでサーバを立てる

それでは下準備ができたので、Oracle Cloudのコンソールに戻ってサーバを立てましょう。コンソールにサインインしたら、［VMインスタンスの作成］をクリック（@<img>{startSSL_46}）します。ちなみにOracle Cloudにはデータベース管理やストレージなど、さまざまなサービスがありますが、クラウドサーバや物理サーバなどのサーバが立てられるサービスは「コンピュート」と呼ばれています。そしてOracle Cloudではサーバのことを、@<ttb>{インスタンス}と呼びます。ここから先でインスタンスと書いてあったら「サーバのことだな」とだと思ってください。

//image[startSSL_46][［VMインスタンスの作成］をクリック][scale=0.8]{
//}

［インスタンスの命名］に［startSSLInstance］と入力します。（@<img>{startSSL_54}）その下の［オペレーティング・システムまたはイメージ・ソースを選択します］は、何も変更せずそのままで構いません。

//image[startSSL_54][［インスタンスの命名］に［startSSLInstance］と入力][scale=0.8]{
//}

パソコンにはOSという基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

本著では、OSはデフォルトの［Oracle Linux 7.7］を使用します。Oracle LinuxならOracle Cloudのツールがあらかじめ入っていますので、@<ttb>{Oracle Linuxでサーバを立てるときはOSはOralce Linuxにする}ことをお勧めします。Oracle LinuxはRed Hat系のディストリビューションですので、RHELやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

2020年1月時点で、Oracle Linuxには次の2種類があります。

 * Oracle Linux 6.10
 * Oracle Linux 7.7

名前のとおり、Oracle Linux 6.10はCentOS 6と同じRHEL6系、Oracle Linux 7.7はCentOS 7と同じRHEL7系なので、使い勝手はほぼ同じです。

さらに下に進んで［SSHキーの追加］は、［SSHキーの貼付け］を選択して、そこに先ほどメモしておいた公開鍵をペーストします。公開鍵は改行を含まず、先頭の「ssh-rsa」から末尾の「<ユーザ名>@<ホスト名>」のようなコメントまでで、まるごと1行です。（@<img>{startSSL_55}）

//image[startSSL_55][［SSHキーの貼付け］を選択してメモしておいた公開鍵をペースト][scale=0.8]{
//}

公開鍵をペーストしたら［作成］をクリックします。

===[column] 【コラム】"Out of host capacity."が起きたらどうすればいい？

さて、元気よく［作成］をクリックしたのに、真っ赤な［Out of host capacity.］が表示されてしまった…という方がいらっしゃると思います。大丈夫、あなたは悪くありません。いま理由を説明するので落ち着いてください。「そんなの表示されなかったよ？」という方は、このコラムは読み飛ばして、この先の「サーバが起動するまで待とう」までジャンプしてください。

//image[startSSL_56]["Out of host capacity."と表示されて何も起きない！][scale=0.8]{
//}

"Out of host capacity."は、直訳すると「ホスト容量が不足しています」という意味ですが、ホストってなんでしょう？

あなたがいまOracle Cloudで立てようとしたサーバは、家でいうと「一軒家」ではなく、マンションの101号室や403号室のような「各部屋」にあたります。このときマンションの建物をホストサーバ、各部屋をゲストサーバと呼びます。

//image[houseAndMansion][マンションの建物をホストサーバ、各部屋をゲストサーバと呼ぶ][scale=0.8]{
//}

「ホストの容量が不足している」ということは…つまり、あなたがOracle Cloudの無料マンションに入居しようとしたら、「ごめんね、無料マンションは大人気でいま空き部屋がないの」と断られてしまった、という状況なのです。

Oracle CloudのAlways Freeは有効期限なしでずっと無料で使える、とても魅力的なサービスです。そのためOracle Cloud側も定期的に新築マンションを追加しているものの、定期的にリソース不足に陥ってはこういう状況になるようです。

この"Out of host capacity."が発生してしまった場合、次のどちらかが起きてホストの容量不足が解消しない限り、Always Freeの枠でサーバは立てられません。

 * 自分以外のユーザーがサーバーを解約してリソースを開放する
 * Oracle Cloudがリソースを増やす
 
ですが、Always Freeとは別に、我々には30日間だけ有効な$300の無償クレジットが与えられています。たとえ無料マンションが満室でも、有料マンションなら空きがあります。30日経ったら消えてしまう$300のお小遣いを握りしめたら、次の方法で有料マンションのお部屋を借りにいきましょう！

===[/column]

=== Always Freeではなく無償クレジットの枠でサーバを立てる

次の手順は、"Out of host capacity."が表示された人だけ実施してください。

もともと選択していたのは［Always Free対象］のマークが付いた［VM.Standard.E2.1.Micro (仮想マシン)］という種類のサーバでした。"Out of host capacity."を回避するため、少し上にスクロールして［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリックしましょう。（@<img>{startSSL_57}）

//image[startSSL_57][［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリック][scale=0.8]{
//}

Oracle Cloudでは、サーバスペックごとに「シェイプ」という区分があります。@<fn>{whatIsShape}インスタンスのシェイプを、いま選択されている［VM.Standard.E2.1.Micro］から変更したいので［シェイプの変更］をクリックしてください。

//footnote[whatIsShape][シェイプとはサーバスペックごとの区分のことです。AWSのインスタンスタイプと同じものだと思ってください]

//image[startSSL_58][［シェイプの変更］をクリック][scale=0.8]{
//}

OCPU@<fn>{ocpu}が2、メモリが16GBの［VM.Standard.E2.2］@<fn>{shapeName}にチェックを入れて、［シェイプの選択］をクリックしましょう。

//footnote[ocpu][OCPUはOracle Compute Unitsの略で、ごく簡単に言うと物理CPUです。OCPU（物理CPU）1つは、vCPU（仮想CPU）2つに相当しますので、もし「AWSのEC2でvCPUが4のサーバを使っている。同等スペックのサーバを用意してほしい」と頼まれたら、Oracle CloudではOCPUが2のシェイプを選べば大丈夫です。単純に数字だけで比較して、OCPUが4のシェイプを選ぶとCPUのスペックが今までの倍になってしまいますので注意してください]

//footnote[shapeName][シェイプの名前は、まず接頭辞が「VM」なら仮想サーバ（Virtual Machine）、「BM」なら物理サーバ（Bare Metal）を表しています。その後ろの単語は「Standard」（汎用）や「DenseIO」（高密度IO）といった特徴、3番目の「E2」や「3」はシェイプの世代、最後の「2」や「8」はOCPUの数を表しています]

//image[startSSL_59][「VM.Standard.E2.2」に変更して［シェイプの選択］をクリック][scale=0.8]{
//}

それ以外は何も変更せずに、いちばん下の［作成］をクリックします。

//image[startSSL_60][［作成］をクリック][scale=0.8]{
//}

=== サーバが起動するまで待とう

オレンジ色で［プロビジョニング中...］と表示されたら、サーバが用意されるまでそのまま数分待ちましょう。

//image[startSSL_61][［プロビジョニング中...］と表示されたら数分待つ][scale=0.8]{
//}

サーバができあがると、表示が緑色の［実行中］に変わります。おめでとうございます！これでサーバが立てられました！

//image[startSSL_62][［プロビジョニング中...］と表示されたら数分待つ][scale=0.8]{
//}

===[column] 【コラム】Oracle Cloudのコンピュートの金額計算方法

ところで、いま立てた「VM.Standard.E2.2」を1ヶ月使ったら、いったいいくら分になるのでしょう？うっかり$300を超えてしまわないか、ちょっと心配なので計算してみましょう。

コンピュートの価格表@<fn>{pricing}を見てみると、［VM.Standard.E2.2］は［$0.03］@<fn>{ocpuNow}と書いてあります。これは［Pay as You Go (OCPU Per Hour)］と書いてあるとおり、1OCPUにつき1時間あたりかかる金額です。@<fn>{awsRegion}

「VM.Standard.E2.2」はOCPUが2なので、$0.03*2で1時間あたり$0.06かかることが分かります。1ヶ月を744時間（24時間*31日）として、$0.06*744時間で$44.64です。

「VM.Standard.E2.2」を1台立てたくらいでは、$300の無償クレジットを使い切ることはないので安心しましょう。ちなみにOracle Cloudでは$1は120円換算@<fn>{rate}なので、日本円だと5356.8円ですね。

===[/column]

//footnote[pricing][@<href>{https://www.oracle.com/jp/cloud/compute/pricing.html}]
//footnote[ocpuNow][2020年1月時点の金額]
//footnote[awsRegion][ちなみにAWSは、同スペックのサーバでもリージョンごとに価格が異なりますが、Oracle Cloudはどこのリージョンでも同一の価格です]
//footnote[rate][$1を120円で換算すると$44.64*120円で5356.8円です]

===[column] 【コラム】Oracle CloudとAWSはどっちが安い？

Oracle Cloudは他のクラウドに比べて価格が安いのが特徴のひとつです。どれくらい安いのか、同じスペックのサーバでAWSと比較してみましょう。

例えば同スペックのVM.Standard.E2.1（Oracle Cloud）とm5.large（AWS）を比較すると、Oracle Cloudの価格はAWSの4分の1以下です。（@<table>{oracleAwsDiff}）

//table[oracleAwsDiff][Oracle CloudとAWSの価格比較]{
　	Oracle Cloud	AWS
------------------------------------
インスタンスの種類	VM.Standard.E2.1	m5.large
CPU	OCPU:1（vCPU:2相当）	vCPU:2
メモリ	8GB	8GB
1時間あたり	$0.03	$0.124
月額	2678.4円	11070.72円
//}

シェアトップを独走するAWSに対して、後発は勝つためにコスト面や性能面でそれぞれ大きなメリットを打ち出してきています。AWSが最適なのであればAWSを選択すべきですが、「みんなが使っているから」というだけ理由で、あまり深く考えずにAWSを使っているのであれば、他のクラウドにも目を向けてみることを筆者はお勧めします。

===[/column]

=== 接続先となるサーバのIPアドレス

無事にサーバが「実行中」になったら、接続先となるサーバのIPアドレスを確認してみましょう。

先ほど作成したインスタンス［startSSLInstance］の、［プライマリVNIC情報］（@<img>{instancePublicIPAddress}）にある［パブリックIPアドレス］をメモ（@<table>{IPv4Address}）してください。

//image[instancePublicIPAddress][［プライマリVNIC情報］の［パブリックIPアドレス］をメモしておこう][scale=0.8]{
//}

//table[IPv4Address][インスタンスの［パブリックIPアドレス］]{
例	パブリックIPアドレス
------------------------------------
140.238.33.51	
//}

それではメモしたIPアドレスを使ってサーバに入ってみましょう。

== SSHでサーバに入ってみよう

=== お使いのパソコンがWindowsの場合

Windowsのパソコンを使っている方は、デスクトップの［rlogin_x64］というフォルダの中にある［RLogin.exe］（@<img>{startRLogin01}）をダブルクリックしてRLoginを起動（@<img>{startRLogin02}）してください。起動したら［新規］をクリックします。

//image[startRLogin01][RLogin.exeをダブルクリック][scale=0.6]{
//}

//image[startRLogin02][RLoginが起動したら［新規］をクリック][scale=0.8]{
//}

初めに［エントリー（上）/コメント（下）］の上に［startSSLInstance］と入力します。続いて［ホスト名（サーバーIPアドレス）］に先ほどメモした［パブリックIPアドレス］を入力（@<img>{startRLogin03}）します。［ログインユーザー名］には［opc］と入力してください。opcというのはOracle Linuxのインスタンスを作成すると、最初から存在しているデフォルトユーザです。

//image[startRLogin03][［ホスト名（サーバーIPアドレス）］と［ログインユーザー名］を入力][scale=0.6]{
//}

次に左メニューで［プロトコル］を選択（@<img>{startRLogin04}）したら、［KeepAliveパケットの送信間隔(sec)］にチェックを入れておきます。これを設定しておくとターミナルをしばらく放っておいても接続が勝手に切れません。続いて［認証キー］をクリックします。

//image[startRLogin04][［KeepAliveパケットの送信間隔(sec)］にチェックを入れて［認証キー］をクリック][scale=0.6]{
//}

［認証キー］リストで［startSSLKey］にチェックが入っていることを確認（@<img>{startRLogin05}）します。これは「ログインするときにこの鍵を使います」というリストです。チェックが入っていたら［OK］をクリックして閉じて構いません。

//image[startRLogin05][［startSSLKey］にチェックが入っていることを確認][scale=0.8]{
//}

続いて左メニューで「クリップボード」を選択（@<img>{startRLogin06}）したら、「左クリックの範囲指定だけでクリップボードにコピーする」と「コピー時に範囲指定を解除しない」にチェックを入れて「右クリックでペースト」を選択します。

//image[startRLogin06][右クリックや左クリックの設定][scale=0.6]{
//}

次に左メニューで「フォント」を選択（@<img>{startRLogin07}）したら、文字セットを「UTF-8」に変更します。すべて設定できたら「OK」をクリックしてください。

//image[startRLogin07][文字セットを「UTF-8」に変更][scale=0.6]{
//}

設定が保存できたら「OK」をクリック（@<img>{startRLogin08}）してください。

//image[startRLogin08][設定が保存できたら「OK」をクリック][scale=0.8]{
//}

すると初回のみ、この「公開鍵の確認」が表示（@<img>{startRLogin09}）されます。これは「初めて入るサーバだけど信頼していいですか？本当に接続しますか？」と聞かれているので、「接続する」をクリックしてください。サーバにはそれぞれフィンガープリントという固有の指紋があるため、下部の「この公開鍵を信頼するリストに保存する」にチェックが入っていればRLoginが覚えていてくれて、次回以降は「これは前に信頼していいって言われたサーバだ！」と判断してそのまま接続させてくれます。

//image[startRLogin09][「公開鍵の確認」が表示されたら「接続する」をクリック][scale=0.6]{
//}

続いて「信頼するホスト鍵のリストを更新しますか？」と聞かれたら「はい」をクリック（@<img>{startRLogin10}）してください。

//image[startRLogin10][「信頼するホスト鍵のリストを更新しますか？」と表示されたら「はい」をクリック][scale=0.8]{
//}

「opc@startsslinstance」と表示（@<img>{startRLogin11}）されたら無事サーバに入れています。SSHでのログイン成功、おめでとうございます！

//image[startRLogin11][「opc@startsslinstance」と表示されたら成功！][scale=0.8]{
//}

もし「opc@startsslinstance」と表示されず、代わりに「SSH2 User Auth Failure "publickey,gssapi-keyex,gssapi-with-mic" Status=1004 Send Disconnect Message... gssapi-with-mic」というようなエラーメッセージが表示（@<img>{startRLogin12}）されてしまったら、これは「鍵がない人は入れないよ！」とお断りされている状態です。［認証キー］リストで［startSSLKey］にチェックが入っていないものと思われますので［認証キー］の設定を確認してみてください。

//image[startRLogin12][このエラーが表示されたら［認証キー］を確認しよう][scale=0.6]{
//}

「接続済みの呼び出し先が一定の時間を過ぎても正しく応答しなかったため、接続できませんでした。」というエラーメッセージが表示（@<img>{startRLogin13}）されてしまった場合は、「ホスト名（サーバーIPアドレス）」に書いた「パブリックIPアドレス」が間違っているものと思われます。「ホスト名（サーバーIPアドレス）」のIPアドレスを確認してみてください。

//image[startRLogin13][このエラーが表示されたら「ホスト名（サーバーIPアドレス）」のIPアドレスを確認しよう][scale=0.8]{
//}

=== お使いのパソコンがMacの場合

Macを使っている方は、ターミナル（@<img>{mac04}）を起動してください。

//image[mac04][最初からインストールされている「ターミナル」を使おう][scale=0.8]{
//}

ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索（@<img>{mac05}）すれば起動できます。

//image[mac05][どこにあるのか分からなかったらSpotlightで「ターミナル」と検索][scale=0.8]{
//}

そして開いたターミナルで次の文字を入力してReturnキーを押します。これはサーバに入るときに使う鍵をオーナー以外が使えないよう、chmodというコマンドで読み書き権限を厳しくしています。この作業は最初の1回だけで構いません。もし「start-aws-keypair.pem」を保存した場所がデスクトップ以外の場合は適宜書き換えてください。

//cmd{
chmod 600 ~/Desktop/startSSLKey
//}

続いてターミナルで次の文字を入力したら再びReturnキーを押します。「パブリックIPアドレス」の部分は先ほどメモした「パブリックIPアドレス」に書き換えてください。-iオプションは「サーバにはこの鍵を使って入ります」という意味ですので、「startSSLKey」を保存した場所がデスクトップ以外だった場合はこちらも適宜書き換えてください。

//cmd{
ssh opc@パブリックIPアドレス -i ~/Desktop/startSSLKey
//}

初回のみ次のようなメッセージが表示されますが、これは「初めて入るサーバだけど信頼していいですか？本当に接続しますか？」と聞かれていますので、「yes」と打ってReturnキーを押してください。するとMacはちゃんとこのサーバのことを覚えてくれて、次回以降は「これは前に信頼していいって言われたサーバだ！」と判断してそのまま接続させてくれます。

//cmd{
Are you sure you want to continue connecting (yes/no)?
//}

「opc@startsslinstance」と表示されたら無事サーバに入れています。おめでとうございます！

今後は今やったのと同じやり方をそのまま繰り返せばサーバにログインできます。ドメイン名というとどうしても「ブラウザで入力してサイトを見るときに使うもの」というイメージがありますが、「名前からIPアドレスが引けるもの」なのでこういう使い方もできるのです。

== ターミナルでサーバを操作・設定してみよう

ようやくサーバに入れたので、ここからはターミナルの基本的な操作を試してみましょう。

=== ターミナルの基本操作に慣れよう

==== プロンプトとは？

では黒い画面で何回かEnterキー（あるいはReturnキー）を押してみましょう。（@<img>{startSSL_63}）普通に改行されますよね。

//image[startSSL_63][Enterキーを押すと改行されて、プロンプトが常に表示されている][scale=0.8]{
//}

このとき左側にずっと出ている次のような表示は「プロンプト」といって、ログインしているユーザ名やサーバの名前などが表示されています。

//cmd{
[opc@startsslinstance ~]$
//}

プロンプトを見ると今は「opc」という一般ユーザであることが分かります。これからサーバに色んな設定をしたいのですが、一般ユーザだと権限がないので「root」という全権限をもったユーザになりましょう。

//cmd{
$ sudo su -
//}

と書いてEnterキーを押すとrootになれます。（@<img>{startSSL_64}）「$」はプロンプトを表していますので入力しないでください。rootになれたらまた何回かEnterキーを押して改行してみましょう。

//image[startSSL_64][sudo su -を書いてEnterキーを押すとrootになれる][scale=0.8]{
//}

いちばん左側に出ているプロンプトが次のように変化しましたか？

//cmd{
[root@startsslinstance ~]# 
//}

ユーザ名が「opc」から「root」に変わりました。それからいちばん右の部分も「$」から「#」に変わっています。プロンプトは@<ttb>{一般ユーザだと「$」で全権を持っているrootだと「#」}という表示になります。今後は「このコマンドをrootで実行してください」のように実行ユーザを詳しく書くことはしませんので、例として書いてある部分のプロンプトが「$」だったらopcのような一般ユーザで実行、「#」だったらrootで実行するんだ、と思ってください。例に「$」や「#」が書いてあってもターミナルで「$」や「#」を自分で入力する必要はありません。

==== コマンドは失敗したときだけエラーを吐く

前述の「sudo su -」のようなものを「コマンド」と呼びます。コマンドとはサーバに対して「あれをして」「これをして」と頼む命令のようなものです。

サーバでコマンドを打った場合、基本的に@<ttb>{上手くいったときは何も言わないで失敗したときだけエラーを吐きます}。ですのでコマンドを打った時に何も表示されなくても不安にならなくて大丈夫です。

先ほどの「私をrootにして！」という命令である「sudo su -」も、上手くいってちゃんとrootになれたのでメッセージは一切出ていないですよね。これが「sudo」を打ち間違えて、こんな風に実行するとどうなるでしょう？

//cmd{
$ sudooo su -
//}

「sudoooなんてコマンドは見つからなかったよ」というエラーメッセージ（@<img>{startSSL_65}）が表示されました。

//image[startSSL_65][「sudooo: command not found」というエラーが表示された][scale=0.8]{
//}

このように何か失敗したときだけエラーが出ます。英語でエラーが出るとそれだけでパニックになってしまいますが、落ち着いてゆっくり読めば「sudooo: command not found…ああ、sudoooっていうコマンドが見つかりませんでした、って書いてある」と判読できると思います。@<ttb>{エラーが出たら声に出してゆっくり読んでみましょう}。

==== ターミナルを閉じたいとき

もう今日の勉強は終わり！サーバとの接続を切ってターミナルを閉じたい、というときはexit（イグジット）というコマンドを叩きます。

//cmd{
# exit
//}

rootになっているときにexitを叩くとopcに戻れます。そしてopcで再びexitを叩くと、サーバの接続を切ってターミナルを閉じることができます。

//cmd{
$ exit
//}

exitをせずに右上の赤い×を押してウィンドウを閉じるのは、電話を切るときに通話オフのボタンを押さずに電話線を引っこ抜くような乱暴な切り方なのでお勧めしません。

=== ミドルウェアをインストール

それでは必要なミドルウェアをインストールしていきましょう。最初にrootになっておいてください。インストールするときはyum（ヤム）というコマンドを使います。

//cmd{
$ sudo su -
//}

先ずはyumで色々アップデートしておきましょう。Windowsアップデートみたいなものです。画面にたくさん文字が流れて、少し時間がかかりますが、最後に［Complete!］と表示されたら問題なく完了しています。（@<img>{startSSL_66}）ちなみに-yオプションはYESを意味するオプションです。-yオプションをつけないで実行すると「これとこれを更新するけどいい？ダウンロードサイズとインストールサイズはこれくらいだよ」という確認が表示されて、yと入力してEnterキーを押さないと更新されません。

//cmd{
# yum update -y
//}

//image[startSSL_66][最後に［Complete!］と表示されたらアップデートは完了][scale=0.8]{
//}

続いてNGINXを入れます。2020年1月現在の安定バージョン@<fn>{version}である1.16系をインストールしたいので、yumのリポジトリ（どこからNGINXをダウンロードしてくるか）にNGINX公式を追加しましょう。

//cmd{
# rpm -ivh http://nginx.org/packages/centos/7/noarch/RPMS/nginx-release-centos-7-0.el7.ngx.noarch.rpm
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

ちょっと分かりにくいかも知れませんが、パソコンにMicrosoft Excelをインストールしたら「表計算というサービスが提供できるパソコン」になるのと同じで、サーバにこのNGINXをインストールすると「リクエストに対してウェブページを返すサービスが提供できるサーバ」、つまりウェブサーバになります。 今回はNGINXを入れましたが、ウェブサーバのミドルウェアは他にもApacheをはじめとして色々な種類があります。

インストールが終わったので、サーバを再起動した場合もNGINXが自動で立ち上がってくるよう、自動起動の設定もオンにしておきましょう。systemctlコマンドで、NGINXの自動起動を有効（enable）にします。

//cmd{
# systemctl enable nginx
# systemctl is-enabled nginx
enabled　←有効になったことを確認
//}

=== FirewalldでHTTPとHTTPSを許可しよう

続いてサーバの中で動いているファイアウォールの設定を変更します。まずは現状、何がファイアウォールを通れるようになっているのか確認してみましょう。

//cmd{
# firewall-cmd --list-services
dhcpv6-client ssh
//}

dhcpv6-clientとsshは通っていいけれど、それ以外は誰であろうと通さないぞ！という設定になっています。このままではブラウザでサイトを見ようとしても、ウェブページを返してくれるはずのNGINXまでリクエストが届きません。そこで次のように、許可対象にhttpとhttpsを追加して、変更が反映されるよう再読み込みします。それぞれ［success］と表示されたら成功しています。

//cmd{
# firewall-cmd --add-service=http --permanent
success

# firewall-cmd --add-service=https --permanent
success

# firewall-cmd --reload
success
//}

これでファイアウォールの設定が変更できたので、もう一度、誰がファイアウォールを通してもらえるのか確認してみましょう。httpとhttpsが追加されていれば問題ありません。

//cmd{
# firewall-cmd --list-services
dhcpv6-client http https ssh
//}

=== SELinuxを無効にしておこう

SELinuxを無効化（disabled）します。

//cmd{
# getenforce
Enforcing　←起動直後は有効になっている

# vi /etc/selinux/config
//}

vi（ブイアイ）はテキストファイルを編集するためのコマンドです。viコマンドでファイルを開くと、最初は次のような「閲覧モード」の画面（@<img>{viSelinux01}）が表示されます。閲覧モードは「見るだけ」なので編集ができません。

//image[viSelinux01][viコマンドでファイルを開いた][scale=0.8]{
//}

この状態でi（アイ）を押すと「編集モード」@<fn>{insertMode}に変わります。（@<img>{viSelinux02}）左下に「-- INSERT --」と表示されていたら「編集モード」です。

//footnote[insertMode][ここでは初心者の方でも直感的に分かるよう「閲覧モード」「編集モード」と呼んでいますが、正しくは「ノーマルモード」「インサートモード」です。]

//image[viSelinux02][i（アイ）を押すと「-- INSERT --」と表示される「編集モード」になった][scale=0.8]{
//}

「編集モード」になるとファイルが編集できるようになります。それでは「SELINUX=enforcing」を「SELINUX=disabled」（@<img>{viSelinux03}）に書き換えてください。

//image[viSelinux03][「SELINUX=enforcing」を「SELINUX=disabled」に書き換える][scale=0.8]{
//}

「編集モード」のままだと保存ができないので書き終わったらESCキーを押します。すると左下の「-- INSERT --」が消えて再び「閲覧モード」になります。（@<img>{viSelinux04}）

//image[viSelinux04][ESCを押すと左下の「-- INSERT --」が消えて再び「閲覧モード」になる][scale=0.8]{
//}

「閲覧モード」に戻ったら「:wq」@<fn>{wq}と入力してEnterキーを押せば変更が保存されます。（@<img>{viSelinux05}）

//image[viSelinux05][「:wq」と入力してEnterキーを押せば保存される][scale=0.8]{
//}

//footnote[wq][書き込んで（write）、抜ける（quit）という命令なのでwqです。]

色々やっているうちになんだか訳が分からなくなってしまって「今の全部なかったことにしたい！取り合えずviからいったん抜けたい！」と思ったときは、ESCキーを押して「:q!」@<fn>{q}と入力してEnterキーを押すと変更を保存せずに抜けることができます。

//footnote[q][保存せずに強制終了（quit!）という命令なのでq!です。]

編集できたらcat（キャット）コマンド@<fn>{cat}でファイルの中身を確認してみましょう。

//cmd{
# cat /etc/selinux/config

# This file controls the state of SELinux on the system.
# SELINUX= can take one of these three values:
#     enforcing - SELinux security policy is enforced.
#     permissive - SELinux prints warnings instead of enforcing.
#     disabled - No SELinux policy is loaded.
SELINUX=disabled
# SELINUXTYPE= can take one of three values:
#     targeted - Targeted processes are protected,
#     minimum - Modification of targeted policy. Only selected processes are protected. 
#     mls - Multi Level Security protection.
SELINUXTYPE=targeted 
//}

以上でSELinuxを無効化する設定は終わりです。

=== OS再起動してみよう

変更した設定を反映させるためreboot（リブート）コマンドでサーバを再起動しておきましょう。

//cmd{
# reboot
//}

SSHの接続も切れてしまいますが、割とすぐに再起動しますので再度RLoginやターミナルで接続（@<img>{viSelinux06}}）してみてください。今度はさっきと同じ設定でそのまま接続できるはずです。

//image[viSelinux06][さっきと同じ設定で接続してみよう][scale=0.8]{
//}

以上で「サーバを立てる」という作業はおしまいです。

=== ターミナルはなんのためにある？

ターミナルでyumやviを叩いてサーバの設定を色々してきましたが、ここで「結局、ターミナルって何なの？」という振り返りをしておきましょう。

@<ttb>{ターミナルはサーバを操作するための画面}です。

皆さんがパソコン使うときはモニタに表示された画面を見ながらキーボードとマウスを使って「フォルダを開いて先週作ったWordファイルを探す」とか「Wordファイルを開いて今週の報告書を書く」というような操作をすると思います。フォルダを開くときは「ダブルクリック」をして、書いた内容を保存するときは「上書き保存する」ボタンを押しますよね。

サーバも同じです。サーバを使うときは「ターミナル」という画面を開いて操作します。ディレクトリ@<fn>{dir}を開いて移動するときはダブルクリックの代わりにcd@<fn>{cd}というコマンドを叩いて移動しますし、ディレクトリの中を見るときもダブルクリックでフォルダを開く代わりにlsコマンドを叩いて見ます。

//footnote[dir][Linuxではフォルダのことをディレクトリと呼びます。]
//footnote[cd][change directoryの略。]

皆さんがいま使っているWindowsやMacといった「パソコン」だったらマウスやキーボードを使ってアイコンやボタンを見ながら操作できますが、サーバは基本的にこの真っ黒な「ターミナル」で文字を打って操作します。パソコンのときはダブルクリックやボタンを押す、という形で伝えていた命令がすべてコマンドに置き換わっていると思ってください。

パソコンもないのにマウスやキーボードだけあっても意味が無いように、ターミナルもそれ単体では何もできません。操作対象であるサーバがあって初めて役に立つ道具なのです。

ちなみにターミナルは背景の色も文字の色も好きに変えられます。どうしても「黒い画面怖い！」という感覚が抜けない人は、ピンクとかオレンジとか好きな色にしてみましょう。@<fn>{color}

//footnote[color][Macのターミナルはそもそも黒じゃなくて白ですね。]

まとめるとターミナルとはサーバを操作するための画面で、操作するときにはコマンドという命令を使います。

=== なぜかサイトが見られない

ウェブサーバも立てたし、SELinuxはとめたし、サーバの中のファイアウォールに穴も空けました。これで準備完了！サーバを立てたときにメモした［パブリックIPアドレス］を、ブラウザで開いてみました。するとしばらくぐるぐるした後で、［接続がタイムアウトしました］と表示されてしまいました。（@<img>{startSSL_77}}）

//image[startSSL_77][なぜかHTTPでサイトが表示されない…][scale=0.8]{
//}

403や404や、あるいは502などのステータスコードも返ってきていないので、そもそもNGINXまでたどり着けていないようです。

=== サーバの手前にあるファイアウォールにも穴をあけよう

さきほどサーバの中にあるファイアウォールの設定を変更して、HTTPとHTTPSが通れるようにしましたが、実はサーバの中だけでなく、サーバの外にももう1つファイアウォールがいます。サイトが表示されなかったのは、「ウェブページを見せて！」というリクエストが、サーバの手前のファイアウォールで阻まれていたためなのです。サーバの手前にあるファイアウォールにも穴を空けて、HTTPとHTTPSがサーバまでたどり着けるようにしましょう。

再びOracle Cloudのコンソールに戻って、左上の［ハンバーガーメニュー］から［コンピュート］の［インスタンス］を開きます。（@<img>{startSSL_68}}）

//image[startSSL_68][［ハンバーガーメニュー］から［コンピュート］の［インスタンス］を開く][scale=0.8]{
//}

インスタンスの一覧が表示されるので［startSSLInstance］をクリックします。（@<img>{startSSL_69}}）

//image[startSSL_69][［startSSLInstance］をクリック][scale=0.8]{
//}

［パブリック・サブネット］をクリックします。（@<img>{startSSL_70}}）

//image[startSSL_70][［パブリック・サブネット］をクリック][scale=0.8]{
//}

もう一度、［パブリック・サブネット］をクリックします。（@<img>{startSSL_71}}）

//image[startSSL_71][もう一度、［パブリック・サブネット］をクリック][scale=0.8]{
//}

［セキュリティ・リスト］の中にある［Default Security List for VirtualCloudNetwork～］をクリックします。（@<img>{startSSL_72}}）このセキュリティ・リストが、サーバの手前にいるファイアウォールです。

//image[startSSL_72][［Default Security List for VirtualCloudNetwork～］をクリック][scale=0.8]{
//}

［イングレス・ルール］で、［イングレス・ルールの追加］をクリックします。（@<img>{startSSL_73}}）

//image[startSSL_73][［イングレス・ルールの追加］をクリック][scale=0.8]{
//}

［ソースCIDR］に［0.0.0.0/0］@<fn>{allowFromAll}を入力します。［宛先ポート範囲］には［80,443］@<fn>{portNumber}を入力します。（@<img>{startSSL_74}}）どちらも入力できたら、［イングレス・ルールの追加］をクリックします。

//footnote[allowFromAll][ソースCIDRは接続元のIPアドレス範囲のことで、0.0.0.0/0はすべてのIPアドレスを指します。つまり接続元がどんなIPアドレスでもファイアウォールを通れます、ということですね]
//footnote[portNumber][ポート番号とは、サーバという家や、その手前のファイアウォールという壁についているドアのようなものだと思ってください。同じサーバを訪問するときでもSSHは22番のドアを、HTTPは80番のドアを、HTTPSは443番のドアを通ります]

//image[startSSL_74][［ソースCIDR］に［0.0.0.0/0］、［宛先ポート範囲］には［80,443］を入力][scale=0.8]{
//}

［イングレス・ルール］に、HTTP（80番ポート）とHTTPS（443番ポート）へのリクエストを通す設定が追加されました。（@<img>{startSSL_75}}）

//image[startSSL_75][ルールが追加された！][scale=0.8]{
//}

=== HTTPでサイトを見てみよう

サーバを立てたときにメモした［パブリックIPアドレス］を、ブラウザで開いてみましょう。（@<img>{startSSL_76}}）

//image[startSSL_76][HTTPでサイトが見られた！][scale=0.8]{
//}

［Welcome to nginx!］と表示されました！これでまず、「HTTPでサイトを表示する」はクリアです。

== ドメイン名の設定

サーバの準備ができたので、HTTPSのサイト用にドメイン名を用意します。自分のドメイン名？そんなの持ってないよ！という人は、先に「DNSをはじめよう」（@<img>{startDNS}}）で、ドメイン名を買ってからこの先へ進むようにしてください。

//image[startDNS][「DNSをはじめよう」（1,000円）はBOOTHやAmazon（Kindle）で好評発売中][scale=0.5]{
//}

あなたが買ったドメイン名を使って「ssl.自分のドメイン名」のAレコードを作成して、サーバの［パブリックIPアドレス］と紐付けてください。ネームサーバはお名前.comを使用してもいいですし、AWSのRoute53で設定しても構いません。

なお筆者が「DNSをはじめよう」で購入したのは@<code>{startdns.fun}というドメイン名だったので、@<code>{ssl.startdns.fun}というAレコードを作って、さっき立てたばかりのサーバの［パブリックIPアドレス］と紐付けます。例えばネームサーバが「お名前.com」なら、DNS設定の画面でこのようにAレコードを追加します。（@<img>{startDNS}}）

//image[onamaeARR][「ssl.自分のドメイン名」のAレコードを作成する][scale=0.6]{
//}

Aレコードができたかどうかは、次のdigコマンドで確認できます。digコマンドをたたいた結果、サーバのIPアドレスが返ってくればAレコードは設定できています。

//cmd{
$ dig ssl.自分のドメイン名 a +short
//}

筆者の場合は、次のように表示されました。

//cmd{
$ dig ssl.startdns.fun a +short
140.238.33.51
//}

ドメイン名が設定できたら、ブラウザでも「http://ssl.自分のドメイン名」を叩いてみましょう。先ほどと同じNGINXのページが表示されるはずです。（@<img>{startSSL_78}}）

//image[startSSL_78][「ssl.自分のドメイン名」でサイトが表示された！][scale=0.8]{
//}


こんなんあった。
https://docs.oracle.com/en/operating-systems/oracle-linux/8/obe-nginx-install/index.html#ConfigureFirewallRules(Optional)

== 証明書を取得しよう
=== 秘密鍵を作ろう
=== CSRを作ろう
=== 証明書の取得申請
=== 取得した証明書をサーバに置こう
== HTTPSでサイトを公開
=== LBのところでSSLターミネーションする方法もある
