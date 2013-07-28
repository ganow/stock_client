stock_client
============

made by Yoshihiro NAGANO

### 概要

このプログラムは、
ネプロ最終課題仮想株取引プログラムのクライアントです。

### 使用方法

###### クライアントを単独で起動する

    ./(バイナリ名) 接続先 接続先ポート番号

    ex)
    ./client localhost 12345

###### まとめて4つのクライアントを起動する

四つとも同じバイナリを起動

    python send.py 接続先 接続先ポート番号 バイナリ名

一つのみ特定のクライアントで、それ以外はなにもしないクライアントを起動

    python send.py 接続先 接続先ポート番号 modeking バイナリ名

### それぞれのバイナリの説明

###### client

一番メイン(のつもり)のクライアントです。
スタンダードな戦略を取ります。(現在はbuysellと同様)

###### buysell

偶数ターンは購入、
奇数ターンは売却を繰り返すクライアント。

###### do_nothing

その名のとおり、
接続するのみで何もリクエストしないクライアント。
デバッグ用。

###### test

リクエストは何もせずに株価変動を監視してその結果のみを出力するクライアント

###### attack_v1

2013/7/18時点で有効だったAttackを実装したクライアント。
サーバーを落とすことが目的。

###### aimbug_v1

2013/7/18時点でのサーバーの不具合をつくことで、
莫大な所持金を得ることができるクライアント。
保有株価も資産にカウントし考慮した上で、
その資産を用いて常に毎ターン購入を繰り返す。

###### aimbug_v2

恐らく有効であると思われる新たな不具合をつくクライアント。
(2013/7/29現在サーバーのバグが改善していないため検証不可)
存在しない株の売却を繰り返すことで、
その会社の株価を大幅に繰り下げ、
株価が0を下回った時点で最大数を購入する。
少しでも株価が上がった時点で全て売却して終了

###### aimbug_v2_with_attack_v2

上記の戦略にAttack_ver2を合わせたもの。
もともとのAttack関数はサーバーのsegmentation faultを目的とした戦略兵器であったのに対し、
こちらのAttack_ver2はあくまでもサーバーに継続的に負荷をかけ続ける戦術兵器を目指した。
自分のリクエストを全て投げたあとは次のターンに移行するまでwriteとreadを繰り返し、
他のクライアントのリクエストを阻害することを目的とする。