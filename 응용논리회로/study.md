# 190514 Quartus Study
- 작성자 : 유재덕

## 프로젝트 생성
1. 프로젝트 명 -> 엔티티 이름과 똑같이 하자
2. Add file -> 직접 코드 짠 애들을 넣어준다.
3. 코어명 : EP2C35F672C6
4. 코어 선택 완료 후 Finish
5. 도구창 FILE에서 NEW 선택. VHDL 코드 생성.
6. 코드 작성 후 엔티티 이름과 같은 이름으로 코드 저장

## Compile
1. Hierarchy옆에 Files에서 저장한 코드를 Top Entity로 지정해준다.
2. 컴파일
3. Pin Planner에서 각 input들이 어떤 역할 할지 설정해주기 -> import assignment 필요하면 해주자.
   - ex) rst -> SW[0] 스위치를 통해 작동한다고 설정
3. pin planner가 어려우면 Assignment Editor을 활용하자.
4. pin planner에서 설정해주기 귀찮으면 entity 내에서 그냥 assignment에 지정된 이름으로 해도 됨.

## 보드에 올리기
- USB 블라스터 설치해둬야됨
1. Programmer 클릭