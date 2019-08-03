- 7 loop : batch(1개) & channel(1개) & filter(1개) & 폭, 높이(2개) & 상하좌우 이동(2개) & 확장 3개
- convolution 연산만 바꿔주면 된다.
- convolution ref는 건들지 말고, convolution opt를 건들 것.
  - 결과 : 20점
  - 최적화 정도 : 50점
  - 이메일로 제출한 파일로 완벽히 재현 가능 : 10점
  - DDR과 OCM를 활용하는 것이 중요

- 기존 코드를 먼저 실행하고 optimized 코드 실행한다.
  - measure performance : 다른 정도.
  - 최적화는 O3
  - N : batch - 데이터 개수
  - C : channel - 필터 종류(RGB 색상마다 하나)
  - M : filter - 필터 개수
  - F : of height - output height
  - E : of width - output width
  - S : f height - filter height
  - R : f width - filter width


- good idea
  - [Loop optimizations include loop unrolling, interchange, tiling...](http://ieeexplore.ieee.org)
  - assembly programming
  - compiler options