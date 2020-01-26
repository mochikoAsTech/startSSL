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
 * PuTTYjp（@<href>{http://hp.vector.co.jp/authors/VA024651/PuTTYkj.html}）@<fn>{PuTTYjp}

//footnote[PuTTYjp][PuTTYjpを使う場合、.pemの秘密鍵をPuTTYgenで.ppkに変換する必要が出てくるため、他のターミナルソフトに比べると一手間余計にかかります。]

//image[rlogin][RLogin][scale=0.8]{
//}

本著ではいちばん上のRLogin（@<img>{rlogin}）を使って説明していきますので、特にこだわりがなければRLoginを使うことをお勧めします。RLoginの「実行プログラム(64bit)@<fn>{64bit}」（@<img>{downloadRLogin01}）のURL、@<href>{http://nanno.dip.jp/softlib/program/rlogin_x64.zip}をクリックしてください。

//footnote[64bit][もしパソコンのWindowsが32bit版だった場合は「実行プログラム(32bit)」のURLをクリックしてください。]

//image[downloadRLogin01][「実行プログラム(64bit)」のURLをクリックしてダウンロード][scale=0.8]{
//}

ダウンロードしたZIPファイルを保存（@<img>{downloadRLogin02}）します。保存場所はどこでも構いませんが、後でどこに置いたか分からなくなりそうな人はデスクトップに保存しておきましょう。

//image[downloadRLogin02][「ファイルを保存する」でパソコンに保存][scale=0.8]{
//}

デスクトップのZIPファイル（rlogin_x64.zip）を右クリック（@<img>{downloadRLogin03}）して、［解凍＞デスクトップに解凍］@<fn>{lhaplus}をクリックします。

//image[downloadRLogin03][ZIPファイルを右クリックして解凍＞デスクトップに解凍][scale=0.8]{
//}

//footnote[lhaplus][ZIPファイルを右クリックしても「解凍」が見当たらないときは、圧縮・解凍の定番ソフトであるLhaplusをインストールしましょう。 @<href>{https://forest.watch.impress.co.jp/library/software/lhaplus/}]

解凍したら、デスクトップにできた「rlogin_x64」というフォルダの中にある「RLogin.exe」@<fn>{filenameExtension}（@<img>{downloadRLogin04}）をダブルクリックすればRLoginが起動（@<img>{downloadRLogin05}）します。

//footnote[filenameExtension][フォルダの中にRLoginはあるけどRLogin.exeなんて見当たらない・・・という場合、ファイルの拡張子が非表示になっています。この後も拡張子を含めてファイル名を確認する場面が何度かでてきますので、表示されていない人は「拡張子 表示」でGoogle検索して拡張子が表示されるように設定変更しておきましょう。]

//image[downloadRLogin04][RLogin.exeをダブルクリック][scale=0.6]{
//}

//image[downloadRLogin05][RLoginが起動した][scale=0.8]{
//}

これでRLoginのインストールは完了です。

==== WindowsでSSHのキーペア（秘密鍵・公開鍵）を作成する

Windowsの方は、起動したRLoginで［新規(N)］をクリックします。

//image[startSSL_45][［新規(N)］をクリック][scale=0.8]{
//}

左メニューの［プロトコル］を選択して、［認証キー(K)］をクリックします。

//image[startSSL_47][［プロトコル］を選択して［認証キー(K)］をクリック][scale=0.8]{
//}

［任意の名前が指定できます］に［startSSLKey］を入力して、［作成］をクリックします。

//image[startSSL_48][［startSSLKey］を入力して［作成］をクリック][scale=0.8]{
//}

［パスフレーズ］と［パス再入力］には何も入力せず、［OK］をクリックします。@<fn>{whatIsPassPhrase}

//footnote[whatIsPassPhrase][「p@$sw0rd」や「@dm1ni$trat0r」のように、ひとつの単語でできているのがパスワードです。それに対して「This 1s P@s$ Phrase.」のように空白を挟んだ文章（フレーズ）で構成されているのものをパスフレーズと呼びます]

//image[startSSL_49][何も入力せず［OK］をクリック][scale=0.8]{
//}

［空のパスフレーズを指定しています。空のままで処理を続行しますか？］と表示されますが、そのまま［OK］をクリックします。

//image[startSSL_50][［OK］をクリック][scale=0.8]{
//}

［認証キーリスト］に、今作った［startSSLKey］が表示されたら、キーペア（秘密鍵・公開鍵）が無事できています。［公開鍵］をクリックしてください。（@<img>{downloadRLogin04}）

//image[startSSL_51][［startSSLKey］が表示されたら［公開鍵］をクリック][scale=0.8]{
//}

この後すぐに使いますので、表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。公開鍵をメモしたら［OK］をクリックして閉じます。

//footnote[windowsComment][mochikoAsTech@の部分には、<Windowsのユーザ名>@が入ります]

//image[startSSL_52][表示された公開鍵（文字列）はまるごとコピーしてメモ帳にペーストしておこう][scale=0.8]{
//}

あとは［キャンセル］を繰り返しクリックして、起動中のRLoginはいったん閉じてしまって構いません。RLoginはまた後で使いますので、デスクトップの「rlogin_x64」フォルダとその中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。メモした公開鍵も無くさないようご注意ください。

===[column] 【コラム】パスフレーズは設定すべき？しなくてもいい？

秘密鍵に［パスフレーズ］を設定しておくと、鍵を使ってサーバに入ろうとしたとき、「鍵を発動するにはパスフレーズを叫べ…！」という感じでパスフレーズを聞かれます。

つまり、もしあなたの秘密鍵が盗まれて勝手に使われそうになっても、パスフレーズを設定していれば鍵の悪用が防げます。スマホが盗まれてしまっても、パスワードが分からなければロック画面が解除できず、勝手に使えないのと同じです。

ただ「パスワード認証じゃなくて鍵認証なのに、パスフレーズも要るの…？」という点で、初心者を混乱に陥れやすいので、本著では秘密鍵をパスフレーズなしで作って使います。

パスフレーズを設定していれば絶対に安心！というものではありませんが、上記の理由から、本来であれば設定した方がいいものです。

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

逆にコピーした内容をターミナルへペーストしたいときはターミナル上で@<ttb>{右クリックするだけ}です。Ctrl+pは使えないので注意してください。

===[/column]

== コンピュートでサーバを立てる

コンソールにサインインしたら、さっそくサーバを立てましょう。［VMインスタンスの作成］をクリックします。（@<img>{startSSL_46}）

//image[startSSL_46][［VMインスタンスの作成］をクリック][scale=0.8]{
//}

［インスタンスの命名］に［startSSLInstance］と入力します。（@<img>{startSSL_54}）その下の［オペレーティング・システムまたはイメージ・ソースを選択します］は、何も変更せずそのままで構いません。

//image[startSSL_54][［インスタンスの命名］に［startSSLInstance］と入力][scale=0.8]{
//}

パソコンにはOSという基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

今回は、OSはデフォルトの［Oracle Linux 7.7］を使います。Oracle LinuxならOracle Cloudのツールがあらかじめ入っていますので、@<ttb>{Oracle Linuxでサーバを立てるときはOSはOralce Linuxにする}ことをお勧めします。Oracle LinuxはRed Hat系のディストリビューションですので、RHELやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

Oracle Linuxには2020年1月時点で

 * Oracle Linux 6.10
 * Oracle Linux 7.7

の2種類があります。名前のとおり、Oracle Linux 6.10はCentOS 6と同じRHEL6系、Oracle Linux 7.7はCentOS 7と同じRHEL7系なので、使い勝手はほぼ同じです。本著ではOracle Linux 7.7を使用します。

さらに下に進んで［SSHキーの追加］は、［SSHキーの貼付け］を選択して、そこに先ほどメモしておいた公開鍵をペーストします。公開鍵は改行を含まず、先頭の「ssh-rsa」から末尾の「<ユーザ名>@<ホスト名>」のようなコメントまでで、まるごと1行です。（@<img>{startSSL_55}）

//image[startSSL_55][［SSHキーの貼付け］を選択してメモしておいた公開鍵をペースト][scale=0.8]{
//}

公開鍵をペーストしたら［作成］をクリックします。

===[column] 【コラム】"Out of host capacity."が起きたらどうすればいい？

元気よく［作成］をクリックしたのに、真っ赤な［Out of host capacity.］が表示されてしまった…という方がいらっしゃると思います。大丈夫、あなたは悪くありません。いま理由を説明するので落ち着いてください。「そんなの表示されなかったよ？」という方は、このコラムは読み飛ばして［サーバが起動するまで待とう］にジャンプしてください。

//image[startSSL_56]["Out of host capacity."と表示されて何も起きない！][scale=0.8]{
//}

"Out of host capacity."は、直訳すると「ホスト容量が不足しています」という意味ですが、ホストってなんでしょう？

あなたがいまOracle Cloudで立てようとしたサーバは、家でいうと「一軒家」ではなくマンションの101号室や403号室のような「各部屋」にあたります。このときマンションの建物をホストサーバ、各部屋をゲストサーバと呼びます。

「ホストの容量が不足している」ということは…つまり、あなたがOracle Cloudの無料マンションに入居しようとしたら、「ごめんね、無料マンションは大人気でいま空き部屋がないの」と断られてしまった、という状況なのです。

Oracle CloudのAlways Freeは有効期限なしでずっと無料で使える、とても魅力的なサービスなので、順次マンションを建てているものの定期的にリソース不足に陥って、こういう状況になるようです。

この"Out of host capacity."が発生してしまった場合、次の2つが起きてホストの容量不足が解消しない限り、Always Freeの枠でサーバは立てられません。

 * 自分以外のユーザーがサーバーを解約してリソースを開放する
 * Oracle Cloudがリソースを増やす
 
ですが、Always Freeとは別に、我々には30日間だけ有効な$300の無償クレジットがあります！

無料マンションが満室でも、有料マンションなら空きがあります。30日経ったら消えてしまう$300のお小遣いを握りしめて、いざ有料マンションのお部屋を借りにいきましょう！

===[/column]

=== Always Freeではなく無償クレジットの枠でサーバを立てる

もともと選択していたのは［Always Free対象］のマークが付いた［VM.Standard.E2.1.Micro (仮想マシン)］という種類のサーバでした。"Out of host capacity."を回避するため、少し上に戻って［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリックしましょう。（@<img>{startSSL_57}）

//image[startSSL_57][［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリック][scale=0.8]{
//}

Oracle Cloudでは、サーバスペックごとに「シェイプ」という区分があります。@<fn>{whatIsShape}インスタンスのシェイプを、いま選択されている［VM.Standard.E2.1.Micro］から変更したいので［シェイプの変更］をクリックしてください。

//footnote[whatIsShape][シェイプとはサーバスペックごとの区分のことです。AWSのインスタンスタイプと同じものだと思ってください]

//image[startSSL_58][［シェイプの変更］をクリック][scale=0.8]{
//}

OCPU@<fn>{ocpu}が2，メモリが16GBの［VM.Standard.E2.2］@<fn>{shapeName}にチェックを入れて、［シェイプの選択］をクリックしましょう。

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

このように何か失敗したときだけエラーが出ます。英語でエラーが出るとそれだけでパニックになってしまいますが、落ち着いてゆっくり読めば「sudooo: command not found・・・ああ、sudoooっていうコマンドが見つかりませんでした、って書いてある」と判読できると思います。@<ttb>{エラーが出たら声に出してゆっくり読んでみましょう}。

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

インストールが終わったので、サーバを起動した際にNGINXが自動で立ち上がってくるよう、自動起動の設定もオンにしておきましょう。

自動起動の管理対象にhttpd（NGINXのこと）を追加した上で、自動起動をオンにします。

↓ここsysctlの何かに要変更
//cmd{
# chkconfig --add httpd
# chkconfig httpd on
//}

自動起動の設定ができたか確認してみましょう。

//cmd{
# chkconfig --list httpd
httpd           0:off   1:off   2:on    3:on    4:on    5:on    6:off
//}

Linuxにはグラフィカルモードやシングルユーザモードなどランレベルと呼ばれるいくつかのモードがあります。この0から6の数字はランレベルごとの自動起動設定を表しており、現状のランレベルは3なので3のところがonになっていれば大丈夫です。

=== OSの基本設定をしておこう

==== タイムゾーンの設定

date（デート）コマンドでサーバの時間を確認してみましょう。日本はいま18:14なのですが、サーバの時間は9:14でずれてしまっています。

//cmd{
# date
Sat Sep  1 09:14:44 UTC 2018
//}

日本時間になるようタイムゾーンの変更を行いましょう。

//cmd{
# vi /etc/sysconfig/clock
//}

vi（ブイアイ）はテキストファイルを編集するためのコマンドです。viコマンドでファイルを開くと、最初は次のような「閲覧モード」の画面（@<img>{startaws31}）が表示されます。閲覧モードは「見るだけ」なので編集ができません。

//image[startaws31][viコマンドでファイルを開いた][scale=0.8]{
//}

この状態でi（アイ）を押すと「編集モード」@<fn>{insertMode}に変わります。（@<img>{startaws32}）左下に「-- INSERT --」と表示されていたら「編集モード」です。

//footnote[insertMode][ここでは初心者の方でも直感的に分かるよう「閲覧モード」「編集モード」と呼んでいますが、正しくは「ノーマルモード」「インサートモード」です。]


//image[startaws32][i（アイ）を押すと「-- INSERT --」と表示される「編集モード」になった][scale=0.8]{
//}

「編集モード」になるとファイルが編集できるようになります。それでは「ZONE="UTC"」を「ZONE="Asia/Tokyo"」（@<img>{startaws33}）に書き換えてください。

//image[startaws33][「ZONE="UTC"」を「ZONE="Asia/Tokyo"」に書き換える][scale=0.8]{
//}

「編集モード」のままだと保存ができないので書き終わったらESCキーを押します。すると左下の「-- INSERT --」が消えて再び「閲覧モード」になります。（@<img>{startaws34}）

//image[startaws34][ESCを押すと左下の「-- INSERT --」が消えて再び「閲覧モード」になる][scale=0.8]{
//}

「閲覧モード」に戻ったら「:wq」@<fn>{wq}と入力してEnterキーを押せば変更が保存されます。（@<img>{startaws35}）

//image[startaws35][「:wq」と入力してEnterキーを押せば保存される][scale=0.8]{
//}

//footnote[wq][書き込んで（write）、抜ける（quit）という命令なのでwqです。]

色々やっているうちになんだか訳が分からなくなってしまって「今の全部なかったことにしたい！取り合えずviからいったん抜けたい！」と思ったときは、ESCキーを押して「:q!」@<fn>{q}と入力してEnterキーを押すと変更を保存せずに抜けることができます。

//footnote[q][保存せずに強制終了（quit!）という命令なのでq!です。]

編集できたらcat（キャット）コマンド@<fn>{cat}でファイルの中身を確認してみましょう。

//cmd{
# cat /etc/sysconfig/clock
ZONE="Asia/Tokyo"
UTC=true
//}

さらにlnコマンドでシンボリックリンクを作ります。シンボリックリンクはWindowsでいうところのショートカットみたいなものです。

//cmd{
# ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime
//}

ちなみに入力しているパス（path）は入力途中でタブを押すと自動的に補完されるので、全部手打ちしなくても大丈夫です。たとえば

//cmd{
# ln -sf /usr/sh
//}

まで打ってからTabキーを押すと次のように自動補完されます

//cmd{
# ln -sf /usr/share/
//}

シンボリックリンクが生成されたかlsコマンド@<fn>{ls}で確認してみましょう。（@<img>{startaws36}）

//cmd{
# ls -l /etc/localtime
//}

//footnote[ls][lsはlistの略で、名前のとおりファイルを一覧表示してくれるコマンドです。-lはlongの略で「詳細を表示」というオプションです。]

//image[startaws36][シンボリックリンクが生成された][scale=0.8]{
//}

「->」の矢印が実体であるファイルを指しているので、シンボリックリンクができていることがわかります。

==== locale（言語）の設定

続いてlocale（言語）の設定をします。今は言語の設定が英語になっているのでエラーメッセージなども英語で表示されますが、分かりやすくするため言語設定を日本語に変更しましょう。

//cmd{
# vi /etc/sysconfig/i18n
//}

先ほどと同じviコマンドでファイルを開いたらi（アイ）で「編集モード」にして「en_US」の部分を「ja_JP」に書き換えてください。

//cmd{
# vi /etc/sysconfig/i18n
LANG=en_US.UTF-8
↓
LANG=ja_JP.UTF-8
//}

書き終わったらESCキーを押して「閲覧モード」に戻り「:wq」で保存します。編集できたらcat（キャット）コマンドでファイルの中身を確認してみましょう。

//cmd{
# cat /etc/sysconfig/i18n
LANG=ja_JP.UTF-8
//}

通常のLinuxサーバであればこの設定だけでいいのですが、Amazon Linuxの場合、AMIからインスタンスを復元すると今修正した「LANG=ja_JP.UTF-8」がそっと元の「LANG=en_US.UTF-8」に戻ってしまいます。

元に戻らないよう次のファイルも編集しておきましょう。

//cmd{
# vi /etc/cloud/cloud.cfg
//}

viコマンドでファイルを開いたらi（アイ）で「編集モード」にして一番下に次の1行を書き足してください。

//cmd{
locale: ja_JP.UTF-8
//}

書き終わったらESCキーを押して「閲覧モード」に戻り「:wq」で保存します。編集できたらcatコマンドでファイルの中身を確認してみましょう。

//cmd{
# cat /etc/cloud/cloud.cfg
# WARNING: Modifications to this file may be overridden by files in
# /etc/cloud/cloud.cfg.d

# If this is set, 'root' will not be able to ssh in and they 
# will get a message to login instead as the default user (opc)
disable_root: true

# This will cause the set+update hostname module to not operate (if true)
preserve_hostname: true

datasource_list: [ Ec2, None ]

repo_upgrade: security
repo_upgrade_exclude:
 - kernel
 - nvidia*
 - cudatoolkit

mounts:
 - [ ephemeral0, /media/ephemeral0 ]
 - [ swap, none, swap, sw, "0", "0" ]
# vim:syntax=yaml

locale: ja_JP.UTF-8
//}

==== historyの設定

最後にhistoryの設定@<fn>{better}を行います。historyコマンドを叩くと今まで自分が実行したコマンドの履歴が見られます。

//footnote[better][historyの設定は任意ですが、あとで自分の作業を振り返るときに便利なので設定しておくことをお勧めします。]

//cmd{
# history
    1  sudooo su -
    2  yum install -y jwhois mysql
    3  yum install -y php72 php72-mbstring php72-mysqlnd
    4  chkconfig --add httpd
    5  chkconfig httpd on
    6  chkconfig --list httpd
    7  date
    8  vi /etc/sysconfig/clock
    9  cat /etc/sysconfig/clock
   10  ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime
   11  ls -l /etc/localtime
   12  vi /etc/sysconfig/i18n
   13  cat /etc/sysconfig/i18n
//}

とても便利なのですが、このままだと「そのコマンドをいつ実行したのか？」という日時が分かりません。また最大1000件までしか保存されないためそれ以上前の履歴を追うことができません。設定を変更して最大で2000件まで保存されて、日時も表示されるようにしましょう。

//cmd{
# vi /etc/bashrc
//}

先ほどと同じviコマンドでファイルを開くと、最初は「閲覧モード」になっています。「閲覧モード」のままでshift+gを押してファイルの最終行へ移動（@<img>{startaws37}）してください。

//image[startaws37][shift+gで最終行に移動した][scale=0.8]{
//}

最終行に移動したらi（アイ）で「編集モード」にして次の2行を追記してください。

//cmd{
HISTTIMEFORMAT='%F %T '
HISTFILESIZE=2000
//}

書き終わったらESCキーを押して「閲覧モード」に戻り「:wq」で保存します。編集できたらtail（テイル）コマンド@<fn>{tail}でファイルの中身を確認してみましょう。

//cmd{
# tail -2 /etc/bashrc
HISTTIMEFORMAT='%F %T '
HISTFILESIZE=2000
//}

//footnote[tail][tailコマンドは名前のとおりファイルの尻尾、つまり末尾を表示するコマンド。引数で「-2」と指定すれば末尾から2行、「-10」と指定すれば末尾から10行が表示されます。]

以上でOSの基本設定は終了です。変更した設定を有効にするためreboot（リブート）コマンドでサーバを再起動しておきましょう。

//cmd{
# reboot
//}

SSHの接続も切れてしまいますが、割とすぐに再起動しますので再度RLoginやターミナルで接続（@<img>{startaws38}）してみてください。今度はさっきと同じ設定でそのまま接続できるはずです。

//image[startaws38][さっきと同じ設定で接続してみよう][scale=0.8]{
//}

接続できたらdateコマンドでサーバの時間を確認してみましょう。サーバのタイムゾーンが東京になって時間のずれはなくなり、言語も日本語に変わったことで次のように表示されるはずです。

//cmd{
$ date
2018年  9月  1日 土曜日 19:58:14 JST
//}

続いてrootになってhistoryコマンドを叩いてみましょう。rootになったときのメッセージも日本語に変わっていますね。

//cmd{
$ sudo su -
最終ログイン: 2018/09/01 (土) 20:00:12 JST日時 pts/0

# history
    1  2018-09-01 20:01:41 sudooo su -
    2  2018-09-01 20:01:41 ip addr
    3  2018-09-01 20:01:41 hostname
    4  2018-09-01 20:01:41 chkconfig --add httpd
    5  2018-09-01 20:01:41 chkconfig httpd on
    6  2018-09-01 20:01:41 chkconfig --list httpd
    7  2018-09-01 20:01:41 date
    8  2018-09-01 20:01:41 vi /etc/sysconfig/clock
    9  2018-09-01 20:01:41 cat /etc/sysconfig/clock
   10  2018-09-01 20:01:41 ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime
   11  2018-09-01 20:01:41 ls -l /etc/localtime
   12  2018-09-01 20:01:41 vi /etc/sysconfig/i18n
   13  2018-09-01 20:01:41 cat /etc/sysconfig/i18n
   14  2018-09-01 20:01:41 vi /etc/bashrc
   15  2018-09-01 20:01:41 tail -2 /etc/bashrc
   16  2018-09-01 20:01:41 reboot
   17  2018-09-01 20:02:58 date
   18  2018-09-01 20:03:01 history
//}

設定変更してrebootするまでは日時が記録されていなかったためすべて同じ日時になっていますが、reboot後はちゃんと実行した日時が表示されています。@<fn>{historySave}

//footnote[historySave][ちなみにhistoryはターミナルを「exit」して閉じるときに履歴が書き込まれるため、前述の「exit」で抜けずに赤い×を押してウィンドウを閉じたり、ネットワークがぶつっと切れてしまったりするとその分は記録されずに消えてしまいます。]

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
