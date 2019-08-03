Library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counter is
port(
    clk			    : in std_logic;
    rst 			: in std_logic;
    adjSW			: in std_logic;
    modeSW          : in std_logic;
    upSW            : in std_logic;
    curMode	    : in std_logic_vector;
    nextMode	    : out std_logic_vector;
    src_TIME_H1               : in std_logic_vector(3 downto 0);
    src_TIME_H0               : in std_logic_vector(3 downto 0);
    src_TIME_M1               : in std_logic_vector(3 downto 0);
    src_TIME_M0               : in std_logic_vector(3 downto 0);
    src_TIME_S1               : in std_logic_vector(3 downto 0);
    src_TIME_S0               : in std_logic_vector(3 downto 0);
    rst_TIME_H1               : out std_logic_vector(3 downto 0);
    rst_TIME_H0               : out std_logic_vector(3 downto 0);
    rst_TIME_M1               : out std_logic_vector(3 downto 0);
    rst_TIME_M0               : out std_logic_vector(3 downto 0);
    rst_TIME_S1               : out std_logic_vector(3 downto 0);
    rst_TIME_S0               : out std_logic_vector(3 downto 0));
end counter;

architecture behave of counter is
signal	  temp		   : std_logic_vector(3 downto 0) := "0000";
signal    h1               : std_logic_vector(3 downto 0) := "0000";
signal    h0               : std_logic_vector(3 downto 0):= "0000";
signal    m1               :  std_logic_vector(3 downto 0) := "0000";
signal    m0               :  std_logic_vector(3 downto 0) := "0000";
signal    s1               :  std_logic_vector(3 downto 0) := "0000";
signal    s0               :  std_logic_vector(3 downto 0) := "0000";
signal    CNT : std_logic_vector(5 downto 0) := "000000";
signal    state : std_logic_vector(1 downto 0) := "00";
signal    nextstate : std_logic_vector(1 downto 0) := "00";
signal    upspeed : std_logic_vector(3 downto 0) := "0000";

begin


	process(clk, rst)
	begin
    if rst = '0' then
      upspeed <= "0001";
      h1 <= "0001";
      h0 <= "0010";
      m1 <=(others => '0');
      m0 <=(others => '0');
      s1 <=(others => '0');
      s0 <=(others => '0');
      state <= (others => '0');
      nextstate <=(others => '0');
      CNT <= (others => '0');
		end if;
      if clk = '1' and clk'EVENT then
          state <= curMode;
          case state is
            when "00" =>
            -- clock     

              temp <= temp + 1;
              if temp = "1001" then
                  temp <= (others => '0');
                  s0 <= s0 + 1;
                  if s0 = "1001" then
                      s0 <= (others  =>'0');
                      s1 <= s1 + 1;
                      if(s1  = "0101") then
                          s1 <= (others => '0');
                          m0 <= m0 + 1;
                          if m0 = "1001" then
                              m0 <= (others => '0');
                              m1 <= m1 + 1;
                              if m1 = "0101" then
                                  m1 <= (others => '0');
                                  h0 <= h0 + 1;
                                  if h0 = "1001" then
                                      h0 <= (others => '0');
                                      h1 <= h1 + 1;
                                  end if;
                                  if h0 = "0011" then
                                      if(h1 = "0010" and h0 = "0011") then
                                          h1 <= (others => '0');
                                          h0 <= (others => '0');
                                      end if;
                                  end if;
                              end if;
                          end if;
                      end if;
                  end if;
              end if;

              if(adjSW = '0') then         
                  CNT <= CNT + 1;
                  if(CNT > "010011") then
                      nextstate <= "01";
                      CNT <= (others => '0');
                  else 
                    nextstate <= curMode;
                  end if;
              else
                  CNT <= (others => '0');
                  nextstate <= curMode;
              end if;

            when "01" =>
            -- increase hour

              if(upSW = '0') then
                  CNT <= CNT + 1;

                  if CNT > "001010" then
                      upspeed <= "0010";
                  else 
                      upspeed <= "0001";
                  end if;
 if(h0 + upspeed > "1001") then
              
                case h1 is
                  when "0001" =>
                    if(h0 + upspeed > "1100") then
                      h1 <= (others => '0');
                      h0 <= (others => '0');

                    else
                      h1 <= h1 + 1;
                      h0 <= h0 + upspeed - "1010";
                    end if;
                  when "0010" =>
                    h1 <= (others => '0');
                    h0 <= (others => '0');
		  when others =>
                      h1 <= h1 + 1;
                      h0 <= h0 + upspeed - "1010";
                end case;

              elsif(h0 + upspeed > "0011") then
                if(h1 = "0010") then
                  h1 <= (others => '0');
                  h0 <= (others => '0');
                else
                  h0 <= h0 + upspeed;
                end if;
              else
                h0 <= h0 + upspeed;
              end if;

              else
                  CNT <= (others => '0');
              end if;

             

                

              if(modeSW = '0') then
                  nextstate <= "10";
                  CNT<= (others => '0');
              else 
                  nextstate <= curMode;
              end if;


            when "10" =>
            -- increase minute
                if(upSW = '0') then
                    CNT <= CNT + 1;

                    if CNT > "001010" then
                        upspeed <= "0101";
                    else 
                        upspeed <= "0001";
                    end if;

 if(m0 + upspeed > "1001") then
              
                case m1 is
                  when "0101" =>
                      m1 <= (others => '0');
                      m0 <= (others => '0');

                  when others =>
                      m1 <= m1 + 1;
                      m0 <= m0 + upspeed - "1010";
                    end case;

              else

                  m0 <= m0 + upspeed;
                end if;


                else
                    CNT <= (others => '0');
                end if;

                if(modeSW = '0') then
                    nextstate <= "11";
                    CNT<= (others => '0');
                else 
                    nextstate <= curMode;
                end if;

            when "11" =>
                if(upSW = '0') then
                    s0 <= (others => '0');
                    s1 <= (others => '0');
                end if;

                if(modeSW = '0') then
                    nextstate <= "00";
                    CNT<= (others => '0');
                else 
                    nextstate <= curMode;
                end if;
	     when others=>
		nextstate <= "00";
        end case;
      end if;
    end process;
    nextmode <= nextstate;
    rst_TIME_H1 <= h1;
    rst_TIME_H0 <= h0;
    rst_TIME_M1 <= m1;
    rst_TIME_M0 <= m0;
    rst_TIME_S1 <= s1;
    rst_TIME_S0 <= s0;
end behave;