= はじめに

//flushright{

2020年3月
mochikoAsTech

//}

本著を手に取ってくださったあなた、こんにちは！あるいは、はじめまして。
「SSLをはじめよう」の筆者、mochikoAsTechです。

SSLは好きですか？それとも怖いですか？本著を書くまで、筆者は「ちゃんと分かっているとは言えないので、SSLを迂闊にさわるのはなんだか怖い」と感じていました。

SSLは、エンジニアのごく身近なところにあります。たとえば「サイトをフルSSL化する」「SSL証明書を更新する」のような形で、誰しも一度はSSLと関わりをもったことがあるのではないでしょうか。しかし関わる機会が多い割に、「ちゃんと分かっているか」と言われるとちょっと自信がない、そんなエンジニアは筆者を含め、きっと一定数いると思っていました。

Googleが2014年ごろからさかんに提唱している「HTTPS everywhere」（直訳すると「すべてをHTTPSで」）のもと、ウェブサイトの基準は「HTTPは普通、HTTPSにすれば安心」から、「HTTPは危険、HTTPSが普通」に変わってきました。ますますSSLと関わる機会が増えてきて、心のどこかで「SSL、ちゃんと分かりたいなぁ…」と思っている。本著はそんな人のための一冊です。

理解度は「分かった！」「分かってなかった…」をくり返して、段々と上がっていくものです。まずは本著で、一緒に最初の「分かった！」まで進んでみましょう。

ちなみに本著「SSLをはじめよう」（以下SSL本）では、「DNSをはじめよう」（以下DNS本）で購入したドメイン名を使用します。DNS本を読まずにSSL本を読み進めていくと、第2章辺りで「ここで事前にあく抜きしておいた筍を取り出します」と言われて、「は？あく抜きとかいつしてたの？！」という状態になります。「DNSは興味ないし面倒くさいんだけど…」という方も、できればDNS本を先にお読みいただいて、筍の下ごしらえ（＝ドメイン名の購入）を済ませた状態でSSL本を開いてみてください。きっとその方が美味しくお召し上がりいただけます。なおSSL本の第1章は、DNS本を読んでいなくても問題ない内容ですので、とりあえずそのまま読み進めていただいても構いません。

またインフラやサーバに関する説明は、すでに「AWSをはじめよう」（以下AWS本）で行なっていますので、本著では最低限にとどめています。本著でHTTPSのサイトを作ってみて、「インフラちょっと楽しいかも」と思われた方は、よかったら後でAWS本も召し上がってみてください。

DNS本、AWS本、そしてSSL本のはじめよう3部作は、「サーバやインフラは怖いものではなくすごく楽しいものなんだよ」ということを、かつての私のようなインフラ初心者へ伝えたくて書いたシリーズです。

読んで試して「面白かった！」と思ってもらえたら、そしてインフラを前より少しでも好きになってもらえたら何より嬉しいです。

== 想定する読者層

本著は、こんな人に向けて書かれています。

 * よく分からないままネットの手順通りにSSLを設定している人
 * 「サイトをHTTPS化したいな」と思っている人
 * 証明書の購入や設置の流れがいまいち分かっていない人
 * SSLとTLSの関係性がよく分からない人
 * SSL証明書が一体何を証明しているのか知らない人
 * これからシステムやプログラミングを学ぼうと思っている新人
 * ウェブ系で開発や運用をしているアプリケーションエンジニア
 * 「インフラがよく分からないこと」にコンプレックスのある人

== マッチしない読者層

本著は、こんな人が読むと恐らく「not for meだった…（私向けじゃなかった）」となります。

 * SSL/TLSの通信をC言語で実装したい人
 * 「プロフェッショナルSSL/TLS」を読んで完全に理解できた人

== 本著の特徴

本著では実際にサーバを立ててSSL証明書の設置を行い、HTTPSのサイトを作ってみます。手を動かして試してから仕組みを学べるので理解がしやすく、インフラ初心者でも安心して読み進められる内容です。Oracle Cloudの無料枠の中でサーバを立てて使用しますので、サーバ代はかかりません。SSL証明書代のみ、1,000円（税抜）かかります。

またSSLをめぐって実際にやってしまいがちな失敗、トラブルをとり上げて、

 * こんな障害が起きたら原因はどう調べたらいいのか？
 * 問題をどう解決したらいいのか？
 * どうしたら事前に避けられるのか？

を解説するとともに、クイズ形式で反復学習するためのドリルもついています。

== 本著のゴール

本著を読み終わると、あなたはこのような状態になっています。

 * SSL証明書がどんな役割を果たしているのか説明できる
 * 証明書を買うときの手順が分かっている
 * 意図せず「保護されていない通信」と表示されてしまったときの対処法が分かる
 * 障害が起きたときに原因を調査できる
 * 読む前よりSSLが好きになっている
 * SSL/TLSと併記されている「TLS」の意味が分かっている

== 免責事項

本著に記載されている内容は筆者の所属する組織の公式見解ではありません。

また本著はできるだけ正確を期すように努めましたが、筆者が内容を保証するものではありません。よって本著の記載内容に基づいて読者が行なった行為、及び読者が被った損害について筆者は何ら責任を負うものではありません。

不正確あるいは誤認と思われる箇所がありましたら、必要に応じて適宜改訂を行いますのでGitHubのIssueやPull requestで筆者までお知らせいただけますと幸いです。

@<href>{https://github.com/mochikoAsTech/startSSL}
