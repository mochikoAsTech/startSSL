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

左メニューの［サーバー>プロトコル］を選択して、［認証キー(K)］をクリックします。

//image[startSSL_47][［サーバー>プロトコル］を選択して［認証キー(K)］をクリック][scale=0.8]{
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

//image[startSSL_51][キーペアが出来たら［キャンセル］してRLoginを閉じよう][scale=0.8]{
//}

この後すぐに使いますので、表示された公開鍵（ssh-rsaから始まる文字列）をまるごとコピーして、メモ帳などにペーストしておきましょう。

//footnote[windowsComment][mochikoAsTech@の部分には、<Windowsのユーザ名>@が入ります]

//image[startSSL_52][表示された公開鍵（文字列）はまるごとコピーしてメモ帳にペーストしておこう][scale=0.8]{
//}

公開鍵をメモしたら［キャンセル］を繰り返し4回クリックして、起動中のRLoginはいったん閉じてしまって構いません。RLoginはまた後で使いますので、デスクトップの「rlogin_x64」フォルダとその中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。

===[column] 【コラム】パスフレーズは設定すべき？しなくてもいい？

秘密鍵に［パスフレーズ］を設定しておくと、鍵を使ってサーバに入ろうとしたとき、「鍵を発動するにはパスフレーズを叫べ…！」という感じでパスフレーズを聞かれます。

つまり、もしあなたの秘密鍵が盗まれて勝手に使われそうになっても、パスフレーズを設定していれば鍵の悪用が防げます。スマホが盗まれてしまっても、パスワードが分からなければロック画面が解除できず、勝手に使えないのと同じです。

ただ「パスワード認証じゃなくて鍵認証なのに、パスフレーズも要るの…？」という点で、初心者を混乱に陥れやすいので、本著では秘密鍵をパスフレーズなしで作って使います。

パスフレーズを設定していれば絶対に安心！というものではありませんが、上記の理由から、本来であれば設定した方がいいものです。

===[/column]

起動したRLoginはいったん「キャンセル」をクリックして閉じてしまって構いません。また後で使いますので、デスクトップの「rlogin_x64」フォルダとその中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。

=== お使いのパソコンがMacの場合

Macを使っている方は、最初から「ターミナル」（@<img>{mac02}）というソフトがインストールされていますのでそちらを利用しましょう。

//image[mac02][最初からインストールされている「ターミナル」を使おう][scale=0.8]{
//}

ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索（@<img>{mac01}）すれば起動できます。

//image[mac01][どこにあるのか分からなかったらSpotlightで「ターミナル」と検索][scale=0.8]{
//}

==== MacでSSHのキーペア（秘密鍵・公開鍵）を作成する

Macの方は、ターミナルで次のコマンドを実行してください。@<fn>{tilde}

//footnote[tilde][@<code>{ssh-keygen}コマンドは名前のとおり、SSHの鍵（key）を生成（generate）するコマンドです。-fオプションでは、生成する鍵のファイル名を指定しています。~（チルダ）はホームディレクトリを表しますので、@<code>{-f ~/startSSLKey}は「/Users/<ユーザ名>/startSSLKey」という鍵を作って、という意味です]

//cmd{
ssh-keygen -f ~/startSSLKey
//}

すると次のように、パスフレーズの入力待ち状態になります。何も入力せずに、2回Enterを押してください。

//cmd{
$ ssh-keygen -f ~/startSSLKey
Generating public/private rsa key pair.
Enter passphrase (empty for no passphrase): 　←何も入力せずにEnter
Enter same passphrase again: 　←何も入力せずにEnter
//}

次のように表示されたらキーペア（秘密鍵・公開鍵）の作成は完了です。

//cmd{
$ ssh-keygen -f ~/startSSLKey
Generating public/private rsa key pair.
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/mochikoAsTech/startSSLKey.
Your public key has been saved in /home/mochikoAsTech/startSSLKey.pub.
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

//footnote[macComment][mochikoAsTech@hostnameの部分は、<Macのユーザ名>@<Macのホスト名>が入るので人によって異なります]

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

［インスタンスの命名］に［startSSLInstance］と入力します。（@<img>{startSSL_54}）

//image[startSSL_54][［インスタンスの命名］に［startSSLInstance］と入力][scale=0.8]{
//}

その下の［オペレーティング・システムまたはイメージ・ソースを選択します］は、何も変更せずそのままで構いません。

パソコンにはOSという基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

今回は、OSはデフォルトの［Oracle Linux 7.7］を使います。Oracle LinuxならOracle Cloudのツールがあらかじめ入っていますので、@<ttb>{Oracle Linuxでサーバを立てるときはOSはOralce Linuxにする}ことをお勧めします。Oracle LinuxはRed Hat系のディストリビューションですので、RHELやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

Oracle Linuxには2020年1月時点で

 * Oracle Linux 6.10
 * Oracle Linux 7.7

の2種類があります。名前のとおり、Oracle Linux 6.10はCentOS 6と同じRHEL6系、Oracle Linux 7.7はCentOS 7と同じRHEL7系なので、使い勝手はほぼ同じです。本著ではOracle Linux 7.7を使用します。

［SSHキーの追加］は、［SSHキーの貼付け］を選択して、そこに先ほどメモしておいた公開鍵をペーストします。公開鍵は改行を含まず、先頭の「ssh-rsa」から末尾の「<ユーザ名>@<ホスト名>」のようなコメントまでで、まるごと1行です。（@<img>{startSSL_55}）

//image[startSSL_55][［SSHキーの貼付け］を選択してメモしておいた公開鍵をペースト][scale=0.8]{
//}

公開鍵をペーストしたら［作成］をクリックします。

===[column] 【コラム】"Out of host capacity."が起きたらどうすればいい？

元気よく［作成］をクリックしたのに、真っ赤な［Out of host capacity.］が表示されてしまった…という方がいらっしゃると思います。大丈夫、あなたは悪くありません。いま理由を説明するので落ち着いてください。「そんなの表示されなかったよ？」という方は、コラムは読み飛ばして先に進んでしまって構いません。

//image[startSSL_56]["Out of host capacity."と表示されて何も起きない！][scale=0.8]{
//}

"Out of host capacity."は、直訳すると「ホスト容量が不足しています」という意味ですが、ホストってなんでしょう？

あなたがいまOracle Cloudで立てようとしたサーバは、家でいうと「一軒家」ではなくマンションの101号室や403号室のような「各部屋」にあたります。このときマンションの建物をホストサーバ、各部屋をゲストサーバと呼びます。

ホストの容量が不足している…つまり、あなたがOracle Cloudの無料マンションに入居しようとしたら、「ごめんね、無料マンションは大人気でいま空き部屋がないの」と断られてしまった、という状況です。

「Always Free」は有効期限なしでずっと無料で使える、とても魅力的なサービスなので、順次マンションを建てているものの定期的にリソース不足に陥って、こういう状況になるようです。

"Out of host capacity."が発生してしまった場合、次の2つが起きてホストの容量不足は解消しない限り、Always Freeの枠でサーバは立てられません。

 * 自分以外のユーザーがサーバーを解約してリソースを開放する
 * Oracle Cloudがリソースを増やす
 
ですが、Always Freeとは別に、我々には30日間だけ有効な$300分の無償クレジットがあります！

無料マンションが満室でも、有料マンションなら空きがあります。30日経ったら消えてしまう$300のお小遣いを握りしめて、いざ有料マンションのお部屋を借りにいきましょう！

===[/column]

=== 無償クレジットの枠でサーバを立てる

もともと選択していたのは［Always Free対象］のマークが付いた［VM.Standard.E2.1.Micro (仮想マシン)］という種類のサーバでしたね。少し上に戻って［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリックしましょう。（@<img>{startSSL_57}）

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

オレンジ色で［プロビジョニング中...］と表示されたら、サーバが用意されるまでそのまま数分待ちましょう。

//image[startSSL_61][［プロビジョニング中...］と表示されたら数分待つ][scale=0.8]{
//}

サーバができあがると、表示が緑色の［実行中］に変わります。おめでとうございます！これでサーバが立てられました！

//image[startSSL_62][［プロビジョニング中...］と表示されたら数分待つ][scale=0.8]{
//}

いまサーバが用意されている最中なので、待っている間にちょっと「シェイプ」について学びましょう。

===[column] 【コラム】Oracle Cloudのコンピュートの金額計算方法

いま立てた「VM.Standard.E2.2」を1ヶ月使ったら、いったいいくら分になるのでしょう？

コンピュートの価格表@<fn>{pricing}を見てみると、［VM.Standard.E2.2］は［$0.03］@<fn>{ocpuNow}と書いてあります。これは［Pay as You Go (OCPU Per Hour)］と書いてあるとおり、1OCPUにつき1時間あたりかかる金額です。@<fn>{awsRegion}

「VM.Standard.E2.2」はOCPUが2なので、$0.03*2で1時間あたり$0.06かかることが分かります。1ヶ月を744時間（24時間*31日）として、$0.06*744時間で$44.64です。@<fn>{dollarToYen}

「VM.Standard.E2.2」を1台立てたくらいでは、$300の無償クレジットを使い切ることはないので安心しましょう。

===[/column]

//footnote[pricing][@<href>{https://www.oracle.com/jp/cloud/compute/pricing.html}]
//footnote[ocpuNow][2020年1月時点の金額]
//footnote[awsRegion][ちなみにAWSは、同スペックのサーバでもリージョンごとに価格が異なりますが、Oracle Cloudはどこのリージョンでも同一の価格です]
//footnote[dollarToYen][$1を120円で換算すると$44.64*120円で5356.8円です]

===[column] 【コラム】Oracle CloudとAWSはどっちが安い？

▼Oracle
　VM.Standard.E2.1（OCPU:1, Memory:8GB）
　$0.03/時、つまり2678.4円/月
▼AWS
　m5.large（vCPU:2, Memory:8GB）
　$0.124/時、つまり11070.72円/月

VM.Standard.E2.1におけるOCPU辺りの時間の金額：$0.03
E2.1はCPU1つなので：$0.03
1ヶ月を744時間として：$0.03*744=$22.32
レートは年1回変更で現在は$1が120円なので：$22.32*120=2678.4円

StrageのPricingのURL
https://www.oracle.com/cloud/storage/pricing.html

チュートリアル
https://community.oracle.com/docs/DOC-1019313

Block Volume Storage	$0.0255	GB Storage Capacity / Month
Block Volume Performance UnitsもBalancedかHigher Performanceで積んでおいた方がよさそう

https://docs.oracle.com/cd/E83857_01/get-started/subscriptions-cloud/csgsg/sign-your-account-oracle-cloud-website.html

===[/column]

=== 接続先となるサーバのIPアドレス

サーバに「入る」ということのイメージが付いたところで、接続先となるサーバのIPアドレスを確認してみましょう。

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

Windowsのパソコンを使っている方は、デスクトップの「rlogin_x64」というフォルダの中にある「RLogin.exe」（@<img>{startRLogin01}）をダブルクリックしてRLoginを起動（@<img>{startRLogin02}）してください。起動したら「新規」をクリックします。

//image[startRLogin01][RLogin.exeをダブルクリック][scale=0.6]{
//}

//image[startRLogin02][RLoginが起動したら「新規」をクリック][scale=0.8]{
//}

初めに「エントリー（上）/コメント（下）」に「start-ssl-instance」と入力します。続いて「ホスト名（サーバーIPアドレス）」に先ほどメモした「パブリックIPアドレス」を入力（@<img>{startRLogin03}）します。「ログインユーザー名」には「opc」と入力してください。opcというのはOracle Linuxのインスタンスを作成すると最初から存在しているデフォルトユーザです。

//image[startRLogin03][「ホスト名（サーバーIPアドレス）」と「ログインユーザー名」を入力][scale=0.6]{
//}

続いて「SSH認証鍵」をクリック（@<img>{startRLogin04}）して、デスクトップなど絶対に忘れない場所に保存しておいた「start-aws-keypair.pem」を選択したら「開く」をクリックします。

//image[startRLogin04][「SSH認証鍵」をクリックして「start-aws-keypair.pem」を選択][scale=0.8]{
//}

次に左メニューで「プロトコル」を選択（@<img>{startRLogin05}）したら、「KeepAliveパケットの送信間隔(sec)」にチェックを入れておきます。これを設定しておくとターミナルをしばらく放っておいても接続が勝手に切れません。

//image[startRLogin05][「KeepAliveパケットの送信間隔(sec)」にチェックを入れる][scale=0.6]{
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

もし「opc@startsslinstance」と表示されず、代わりに「SSH2 User Auth Failure "publickey" Status=0004 Send Disconnect Message... none」というようなエラーメッセージが表示（@<img>{startRLogin12}）されてしまったら、これは「鍵がない人は入れないよ！」とお断りされている状態です。恐らく「SSH認証鍵」をクリックして「start-aws-keypair.pem」を選択する作業を忘れているものと思われますので「SSH認証鍵」の設定を確認してみてください。

//image[startRLogin12][このエラーが表示されたら「SSH認証鍵」の設定を確認しよう][scale=0.6]{
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
chmod 600 ~/Desktop/start-aws-keypair.pem
//}

続いてターミナルで次の文字を入力したら再びReturnキーを押します。「パブリックIPアドレス」の部分は先ほどメモした「パブリックIPアドレス」に書き換えてください。-iオプションは「サーバにはこの鍵を使って入ります」という意味ですので、「start-aws-keypair.pem」を保存した場所がデスクトップ以外だった場合はこちらも適宜書き換えてください。

//cmd{
ssh opc@パブリックIPアドレス -i ~/Desktop/start-aws-keypair.pem
//}


初回のみ次のようなメッセージが表示されますが、これは「初めて入るサーバだけど信頼していいですか？本当に接続しますか？」と聞かれていますので、「yes」と打ってReturnキーを押してください。するとMacはちゃんとこのサーバのことを覚えてくれて、次回以降は「これは前に信頼していいって言われたサーバだ！」と判断してそのまま接続させてくれます。

//cmd{
Are you sure you want to continue connecting (yes/no)?
//}

「opc@startsslinstance」と表示されたら無事サーバに入れています。おめでとうございます！

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
