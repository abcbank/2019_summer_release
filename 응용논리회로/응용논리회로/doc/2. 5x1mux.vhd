--- 2. 5x1 mux : 1번 합치는 연습 
library ieee
USE ieee.std_logic_1164.all;
------------------------------------------------------------------------
ENTITY mux is  
    PORT(
        a,b,c,d,e : IN std_logic;
        sel1 : IN std_logic;
        sel2 : IN std_logic;
        sel3 : IN std_logic;
        y : OUT std_logic_vector
    );
------------------------------------------------------------------------
architecture mux OF mux is
begin
    
