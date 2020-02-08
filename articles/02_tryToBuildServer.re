= Oracle Cloudでサーバを立てよう

この章では実際にOracle Cloudでサーバを立てます。

インフラエンジニアのお仕事体験みたいできっと楽しいですよ！

//pagebreak

== 事前準備

=== WindowsでRLoginをインストールする

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

=== WindowsでSSHのキーペア（秘密鍵・公開鍵）を作成する

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

［認証キーリスト］に、いま作った［startSSLKey］が表示されたら、キーペア（秘密鍵・公開鍵）が無事できています。［公開鍵］をクリックしてください。（@<img>{downloadRLogin04}）

//image[startSSL_51][［startSSLKey］が表示されたら［公開鍵］をクリック][scale=0.6]{
//}

この後すぐに使いますので、［クリップボードにコピーされる公開鍵］で表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。公開鍵をメモしたら［OK］をクリックして閉じます。

//footnote[windowsComment][mochikoAsTech@の部分には、<Windowsのユーザ名>@が入ります]

//image[startSSL_52][表示された公開鍵（文字列）はまるごとコピーしてメモ帳にペーストしておこう][scale=0.8]{
//}

あとは［キャンセル］を繰り返しクリックして、起動中のRLoginはいったん閉じてしまって構いません。RLoginは、後でサーバへ入るときに使いますので、デスクトップの「rlogin_x64」フォルダと、その中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。メモした公開鍵も無くさないようご注意ください。

===[column] 【コラム】SSHの秘密鍵にパスフレーズは設定すべき？

秘密鍵に［パスフレーズ］を設定しておくと、鍵を使ってSSHでサーバに入ろうとしたとき、「鍵を発動するにはパスフレーズを叫べ…！」という感じでパスフレーズを聞かれます。

つまり、もしあなたの秘密鍵が盗まれて誰かに勝手に使われそうになっても、パスフレーズを設定していれば鍵の悪用が防げます。スマホ本体が盗まれてしまっても、パスワードが分からなければロック画面が解除できず、勝手に使えないのと同じです。

これは「あなたは何を持っているのか」「あなたは何を知っているのか」「あなたは誰なのか」という複数の要素の中から、2つを用いることで認証の強度を高める「二要素認証」と呼ばれる考え方です。「あなたは秘密鍵を持っている」「あなたはパスフレーズを知っている」という2つの要素を組み合わせることで、単要素での認証よりも強度が高まります。ちなみに「あなたが誰なのか」は指紋認証や顔認証ですね。

ですが「パスワード認証じゃなくて鍵認証なのに、やっぱりパスフレーズが要るの…？」という具合に、初心者を混乱に陥れやすいので、本著では秘密鍵をパスフレーズなしで作って使います。

パスフレーズは「設定していれば絶対に安心！」というものではありませんが、上記の理由から、本来であれば設定した方がいいものです。後で「やっぱり設定しておこう」と思ったら、一度作成した秘密鍵に後からパスフレーズを設定することも可能です。

===[/column]

=== Macでターミナルを準備する

Macを使っている方は、最初から「ターミナル」（@<img>{mac02}）というソフトがインストールされていますのでそちらを利用しましょう。

//image[mac02][最初からインストールされている「ターミナル」を使おう][scale=0.8]{
//}

ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索（@<img>{mac01}）すれば起動できます。

//image[mac01][どこにあるのか分からなかったらSpotlightで「ターミナル」と検索][scale=0.8]{
//}

=== MacでSSHのキーペア（秘密鍵・公開鍵）を作成する

Macの方は、ターミナルで次のコマンドを実行してください。@<fn>{tilde}

//footnote[tilde][@<code>{ssh-keygen}コマンドは名前のとおり、SSHの鍵（key）を生成（generate）するコマンドです。-fオプションでは、生成する鍵のファイル名を指定しています。~（チルダ）はホームディレクトリを表しますので、@<code>{-f ~/Desktop/startSSLKey}は「/Users/<ユーザ名>/Desktop」のフォルダの中に「startSSLKey」という名前の鍵を作って、という意味です]

//cmd{
$ ssh-keygen -f ~/Desktop/startSSLKey
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

=== OSはOracle Linux 7.7を使おう

パソコンにはOSという基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

本著では、OSはデフォルトの［Oracle Linux 7.7］を使用します。Oracle LinuxならOracle Cloudのツールがあらかじめ入っていますので、@<ttb>{Oracle Linuxでサーバを立てるときはOSはOralce Linuxにする}ことをお勧めします。Oracle LinuxはRed Hat系のディストリビューションですので、RHELやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

2020年1月時点で、Oracle Linuxには次の2種類があります。

 * Oracle Linux 6.10
 * Oracle Linux 7.7

名前のとおり、Oracle Linux 6.10はCentOS 6と同じRHEL6系、Oracle Linux 7.7はCentOS 7と同じRHEL7系なので、使い勝手はほぼ同じです。

=== 作っておいたSSHの公開鍵を設置しよう

さらに下に進んで［SSHキーの追加］は、［SSHキーの貼付け］を選択して、そこに先ほどメモしておいた公開鍵をペーストします。公開鍵は改行を含まず、先頭の「ssh-rsa」から末尾の「<ユーザ名>@<ホスト名>」のようなコメントまでで、まるごと1行です。（@<img>{startSSL_55}）

//image[startSSL_55][［SSHキーの貼付け］を選択してメモしておいた公開鍵をペースト][scale=0.8]{
//}

公開鍵をペーストしたら［作成］をクリックします。

=== 〈トラブル〉"Out of host capacity."が起きたらどうすればいい？

さて、元気よく［作成］をクリックしたのに、真っ赤な［Out of host capacity.］が表示されてしまった…という方が一定数いらっしゃると思います。大丈夫、あなたは悪くありません。いま理由を説明するので落ち着いてください。「そんなの表示されなかったよ？」という方は、このコラムは読み飛ばして、この先の「サーバが起動するまで待とう」までジャンプしてください。

//image[startSSL_56]["Out of host capacity."と表示されて何も起きない！][scale=0.8]{
//}

"Out of host capacity."は、直訳すると「ホスト容量が不足しています」という意味ですが、ホストってなんでしょう？

あなたがいまOracle Cloudで立てようとしたサーバは、家でいうと「一軒家」ではなく、マンションの101号室や403号室のような「各部屋」にあたります。このときマンションの建物をホストサーバ、各部屋をゲストサーバと呼びます。

//image[houseAndMansion][マンションの建物をホストサーバ、各部屋をゲストサーバと呼ぶ][scale=0.8]{
//}

「ホストの容量が不足している」ということは…つまり、あなたがOracle Cloudの無料マンションに入居しようとしたら、「ごめんね、無料マンションは大人気でいま空き部屋がないの」と断られてしまった、という状況なのです。

Oracle CloudのAlways Freeは有効期限なしでずっと無料で使える、とても魅力的なサービスです。そのためOracle Cloud側も定期的に新築マンションを追加しているものの、定期的にリソース不足に陥ってはこういう状況になるようです。

この"Out of host capacity."が発生してしまった場合、次のどちらかが起きてホストの容量不足が解消しない限り、Always Freeの枠でサーバは立てられません。

 * 自分以外のユーザーがサーバを解約してリソースを開放する
 * Oracle Cloudがリソースを増やす
 
ですが、Always Freeとは別に、我々には30日間だけ有効な$300の無償クレジットが与えられています。たとえ無料マンションが満室でも、有料マンションなら空きがあります。30日経ったら消えてしまう$300のお小遣いを握りしめたら、次の方法で有料マンションのお部屋を借りにいきましょう！

=== Always Freeではなく無償クレジットの枠でサーバを立てよう

次の手順は、"Out of host capacity."が表示された人だけ実施してください。

もともと選択していたのは［Always Free対象］のマークが付いた［VM.Standard.E2.1.Micro (仮想マシン)］という種類のサーバでした。"Out of host capacity."を回避するため、少し上にスクロールして［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリックしましょう。（@<img>{startSSL_57}）

//image[startSSL_57][［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリック][scale=0.8]{
//}

Oracle Cloudでは、サーバスペックごとに「シェイプ」という区分があります。@<fn>{whatIsShape}インスタンスのシェイプを、いま選択されている［VM.Standard.E2.1.Micro］から変更したいので［シェイプの変更］をクリックしてください。

//footnote[whatIsShape][シェイプとはサーバスペックごとの区分のことです。AWSのインスタンスタイプと同じものだと思ってください]

//image[startSSL_58][［シェイプの変更］をクリック][scale=0.8]{
//}

OCPU@<fn>{ocpu}が2、メモリが16GBの［VM.Standard.E2.2］@<fn>{shapeName}にチェックを入れて、［シェイプの選択］をクリックしましょう。

//footnote[ocpu][OCPUはOracle Compute Unitsの略で、ごく簡単に言うと物理CPUです。OCPU（物理CPU）1つは、vCPU（仮想CPU）2つに相当しますので、もし「AWSのEC2でvCPUが4のサーバを使っている。同等スペックのサーバを用意してほしい」と頼まれたら、Oracle CloudではOCPUが2のシェイプを選べば大丈夫です。単純に数字だけで比較して、OCPUが4のシェイプを選ぶとCPUのスペックがいままでの倍になってしまいますので注意してください]

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

//image[startSSL_62][［実行中］に変わった！サーバが立てられた！][scale=0.8]{
//}

===[column] 【コラム】Oracle Cloudのコンピュートの金額計算方法

ところで、いま立てた「VM.Standard.E2.2」をまるまる1ヶ月使ったら、一体いくら分になるのでしょう？うっかり$300を超えてしまわないか、ちょっと心配なので計算してみましょう。

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
