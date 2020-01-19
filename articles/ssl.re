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

［認証キーリスト］に、今作った［startSSLKey］が表示されたら、キーペア（秘密鍵・公開鍵）の作成は完了です。（@<img>{downloadRLogin04}）

//image[startSSL_51][キーペアが出来たら［キャンセル］してRLoginを閉じよう][scale=0.8]{
//}

［キャンセル］を繰り返し3回クリックして、起動中のRLoginはいったん閉じてしまって構いません。RLoginはまた後で使いますので、デスクトップの「rlogin_x64」フォルダとその中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。

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

Macの方は、ターミナルで次のコマンドを実行してください。

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

ホームディレクトリに秘密鍵（startSSLKey）と、公開鍵（startSSLKey.pub）ができあがっているはずです。

以上で事前準備は完了です。お待たせしました。いよいよサーバを立てましょう。

== コンピュートでサーバを立てる

コンソールにサインインしたら、さっそくサーバを立てましょう。［VMインスタンスの作成］をクリックします。（@<img>{startSSL_46}）

//image[startSSL_46][［VMインスタンスの作成］をクリック][scale=0.8]{
//}

［インスタンスの命名］に［startSSLInstance］と入力します。

パソコンにはOSという基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

今回は、OSはデフォルトの［Oracle Linux 7.7］を使います。Oracle LinuxならOracle Cloudのツールがあらかじめ入っていますので、@<ttb>{Oracle Linuxでサーバを立てるときはOSはOralce Linuxにする}ことをお勧めします。Oracle LinuxはRed Hat系のディストリビューションですので、RHELやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

Oracle Linuxには2020年1月時点で

 * Oracle Linux 6.10
 * Oracle Linux 7.7

の2種類があります。名前のとおり、Oracle Linux 6.10はCentOS 6と同じRHEL6系、Oracle Linux 7.7はCentOS 7と同じRHEL7系なので、使い勝手はほぼ同じです。本著ではOracle Linux 7.7を使用します。

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
