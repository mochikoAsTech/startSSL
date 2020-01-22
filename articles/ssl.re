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
 
ですが、Always Freeとは別に、我々には30日間だけ有効な300ドル（33,000円）分の無償クレジットがあります！

無料マンションが満室でも、有料マンションなら空きがあります。30日経ったら消えてしまう300ドル分のお小遣いを握りしめて、いざ有料マンションを契約しましょう！

===[/column]

=== 無償クレジットの枠でサーバを立てる

もともと選択していたのは［Always Free対象］のマークが付いた［VM.Standard.E2.1.Micro (仮想マシン)］という種類のサーバでした。少し上に戻って［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリックします。（@<img>{startSSL_57}）

//image[startSSL_57][［シェイプ、ネットワークおよびストレージ・オプションの表示］をクリック][scale=0.8]{
//}

Oracle Cloudでは、サーバスペックごとに「シェイプ」という区分があります。@<fn>{whatIsShape}シェイプを、いま選択されている［VM.Standard.E2.1.Micro］から「VM.Standard.E2.2」に変更して、［シェイプの選択］をクリックしましょう。

//footnote[whatIsShape][AWSのインスタンスタイプと同じものだと思ってください]

Oracle CloudのOCPU（物理CPU）1つは、AWSのvCPU（仮想CPU）2つにあたるので、同じスペックで比較するとAWSが4倍以上高い。

▼Oracle
　VM.Standard.E2.1（OCPU:1, Memory:8GB）
　$0.03/時、つまり2678.4円/月
▼AWS
　m5.large（vCPU:2, Memory:8GB）
　$0.124/時、つまり11070.72円/月

E2系におけるOCPU辺りの時間の金額：$0.03
E2.2はCPU2つなので：$0.06（=0.06*120で7.2円）
仮に1ヶ月を744時間として：$0.06*744=$44.64
レートは年1回変更で現在は$1が120円なので：$44.64*120=5356.8円

AWSは同じインスタンスタイプでもリージョンごとに金額が違うけど、Oracle Cloudはどこのリージョンでも金額同じなのか！すごい！

ConputeのPricingのURL
https://www.oracle.com/jp/cloud/compute/pricing.html

StrageのPricingのURL
https://www.oracle.com/cloud/storage/pricing.html

チュートリアル
https://community.oracle.com/docs/DOC-1019313

Block Volume Storage	$0.0255	GB Storage Capacity / Month
Block Volume Performance UnitsもBalancedかHigher Performanceで積んでおいた方がよさそう

命名規則
VMは仮想
BMはベアメタル（物理1台まるごと）
次に
Standard
DenseIO（高密度IO）
とかの種類があって
その後に
E2とか3とかの世代
最後にOCPUの数

¥7.2/時
744時間（31日間）


インスタンスタイプの接頭辞になっている「VM」は仮想サーバ（Virtual Machine）、「BM」は物理サーバ（Bare Metal）を表す。2番目の「Standard」は汎用、「DenseIO」は高密度IOのような特徴、3番目の「E2」や「3」は世代、最後の「2」や「8」はOCPU（物理CPU）の数を表している。

［インスタンスのシェイプ］で［シェイプの変更］をクリックしてください。

https://docs.oracle.com/cd/E83857_01/get-started/subscriptions-cloud/csgsg/sign-your-account-oracle-cloud-website.html

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
