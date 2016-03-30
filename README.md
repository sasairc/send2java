send2java
===

[keepoff07/SendToJava](https://github.com/keepoff07/SendToJava)の、30億のデバイスで走るやつの補完。		
実際にJavaに対しての動作は未確認。（おい）

## Install

```shellsession
% make
# make install
```


## Usage

`-j, --java`及び`-r, --jar`オプションへの引数は、`~/.send2javarc`へ保存されます。

#### -j, --java=JAVA

Java実行環境を指定します。

#### -r, --jar=JAR

`*.jar`コンテナを指定します。

#### -f, --file=FILE

その他、引数として与えたいファイルを指定します。		
ここで指定されたパスは、絶対パスとしてJREへ与えられます。


## License

[WTFPL version 2](http://www.wtfpl.net/txt/copying/)


## Author

sasairc (https://github.com/sasairc)
