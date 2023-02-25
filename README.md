## 돕고 삽니다!

> 개발자는 기술력을 가지고 프로그램을 만든다. 그 프로그램으로 누군가를 도울 때 뿌듯하다🙏🏻

프로그래밍을 모르는 한 친구가 어려움에 빠져 있었습니다.
그 친구를 위해 프로그램을 짜주었던 경험을 적어봅니다.
특정 파일에서 텍스트를 추출하여, 새로운 텍스트 파일(.txt)로 만들어줍니다.

블로그에 상세히 정리를 해두었습니다!
[블로그 링크](https://velog.io/@keinn51/%EC%B9%9C%EA%B5%AC-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8-%EB%A7%8C%EB%93%A4%EC%96%B4%EC%A3%BC%EA%B8%B0-with-C)

## 사용법

mac과 window 중 자신의 운영체제를 찾아서 들어갑니다.

```shell
cd mac
make
./extract_string
```

그 결과 **result.txt** 에 추출한 결과가 나옵니다.


## 목표

### 들어오는 데이터

```shell
# DAY 1
***********************************************
2303.1d shift started by : ABCD/EFGH/WWWW/ACXX    16/JAN/2023 09:00*
****************************************

1004 install and connect DOUGHTNUT
IDONEI CONNECT DOUGHTNUT
 +4eye check : ABCD/LLLL

++++++++++++++++++++++
2303.1d shift ended by : ABCD/EFGH/WWWW/ACXX       16/JAN/2023 09:00*
++++++++++++++++++++++

# DAY 2
***********************************************
2303.1d shift started by : ABCD/CCCC/WWWW/WIOQ     17/JAN/2023 09:00*
****************************************

1004 install and connect SANCHO
IDONEI CONNECT SANCHO
 +4eye check : ABCD/CCCC

1004 install and connect WHALE
IDONEI CONNECT WHALE
 +4eye check : WIOQ/WWWW

++++++++++++++++++++++
2303.1d shift ended by : ABCD/CCCC/WWWW/WIOQ      17/JAN/2023 09:00*
++++++++++++++++++++++
....
```

로직은 아래와 같습니다.

1. `shift started by`가 들어가는 문장을 찾는다. 이 문장에는 날짜 데이터가 들어가 있다.
2. 1번의 문장에 따라 나오는, `4eye check` 가 들어간 문장을 찾는다.
3. 2번의 문장 이전의 문장 중에서 `숫자로 시작하는 문장`을 찾는다.


### 원하는 데이터

```shell
2303.1d shift started by : ABCD/EIDK/WWWW/WIOQ            16/JAN/2023 09:00*
1004 install and connect DOUGHTNUT
+4eye check : ABCD/EIDK

2303.1d shift started by : ABCD/EIDK/WWWW/WIOQ           16/JAN/2023 09:00*
1004 install and connect DOUGHTNUT
+4eye check : ABCD/EIDK
1004 install and connect WHALE
+4eye check : WIOQ/WWWW
```

## 도움이 되었던 링크들

[정적 라이브러리 사용](https://iam777.tistory.com/186)

[정적 라이브러리?](https://wiki.kldp.org/HOWTO/html/Program-Library-HOWTO/static-libraries.html)

[파일 디스크럽터란](https://code4human.tistory.com/123) 

[window에서 현재 작업 경로 얻기](https://blog.naver.com/tipsware/221276143283)

[window에서 make사용하기](https://ndb796.tistory.com/381)

[window에 gcc 컴파일러 설치](https://ddmanager.tistory.com/152)
