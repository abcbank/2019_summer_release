# 연산자 & 속성
## 응용논리회로 2019.03.22 금요일 9:00~12:00
## 201711237 유재덕
목차
1. 연산자
2. 속성
3. 사용자 정의 속성
4. 연산자 오버로딩
5. GENERIC 문
6. 완전한 설계 예
7. 요약

### 1. 연산자
 
- 할당 연산자
  - '<=' : SIGNAL 객체에 어떤 값을 할당
  - ':=' : VARIABLE, CONSTANT, GENERIC에 어떤 값을 할당, 초기값 지정
  - '=>' : 개개의 벡터 요소에 값을 할당, OTHERS로 값을 할당
  - '<='를 사용하는 것을 장려하며 나머지 두 연산자는 어쩔 수 없는 상황이 아닌 이상 사용을 장려하지 않는다. 
  - example
    ```vhdl
    SIGNAL x : STD_LOGIC;
    VARIABLE y : STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL w : STD_LOGIC_VECTOR(0 TO 7);

    x   <= '1';
    y   := "0000";
    w   <= "1000000";
    w   <= (0 => '1'; OTHERS =>'0');
    ```
- 관계 연산자
- 논리 연산자
  - NOT : 우선순위가 가장 높은 연산자.
  - AND, OR, NOR, NAND, XOR, XNOR
  - 피연산자의 데이터는 BIT, STD_LOGIC, STD_ULOGIC(혹은 이들의 벡터 타입)
  - 기본적으로 1게이트 = 1 NAND를 의미하며, 이는 NAND게이트가 가장 쉽게 구성할수 있기 때문이다.
  - example
    ```VHDL
    y   <= NOT a AND b;
    y   <= NOT (a AND b);
    y   <= a NAND b;
    ```
- 시프트 연산자
  - 
- 산술 연산자
  - +, - ,* ,/
  - **, MOD, REM, ABS
- 연쇄연결 연산자
### 2. 속성
### 3. 사용자 정의 속성
### 4. 연산자 오버로딩
### 5. GENERIC 문
### 6. 완전한 설계 예
### 7. 요약  