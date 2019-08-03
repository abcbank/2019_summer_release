Library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity alarm is
port(	
    clk : in std_logic;
    adjsw : in std_logic;
    modesw : in std_logic;
    optionalsw : in std_Logic;

    state : in std_logic;
    nextstate : out std_logic;

    clockH1 : in std_logic_vector(3 downto 0);
    clockH0 : in std_logic_vector(3 downto 0);
    clockM1 : in std_logic_vector(3 downto 0);
    clockM0 : in std_logic_vector(3 downto 0);
    
    alrH1 : out std_logic_vector(3 downto 0);
    alrH0 : out std_logic_vector(3 downto 0);
    alrM1 : out std_logic_vector(3 downto 0);
    alrM0 : out std_logic_vector(3 downto 0);

	ring : out std_logic
	);
end alarm;

architecture BEHAVE of alarm is

signal alarmH1 : std_logic_vector(3 downto 0) := "0001";
signal alarmH0 : std_logic_vector(3 downto 0) := "0010";
signal alarmm1 : std_logic_vector(3 downto 0) := "0000";
signal alarmm0 : std_logic_vector(3 downto 0) := "0000";

signal alrcnt : std_logic_vector(8 downto 0) := "000000000";
signal aupspeed : std_logic_vector(8 downto 0) := "000000000";
signal acnt : std_logic_vector(8 downto 0) := "000000000";
signal atemp : std_logic_vector(8 downto 0) := "000000000";
signal aadjcnt : std_logic_vector(8 downto 0) := "000000000";
signal areadingCount : std_logic_vector(8 downto 0) := "000000000";

constant  asecdiv4				: std_logic_vector(8 downto 0) := "000011001";
constant  aSec					: std_logic_vector(8 downto 0) := "001100100";
constant  afourSec				: std_logic_vector(8 downto 0) := "110010000";
constant  alrtwosec				: std_logic_vector(8 downto 0) := "011001000";
constant  halfsec				: std_logic_vector(8 downto 0) := "001100100";

begin
alrH1 <= alarmH1;
alrH0 <= alarmH0;
alrM1 <= alarmM1;
alrM0 <= alarmM0;

process(clk)
begin
if rst = '0' then
	alarmH1 <= (others => '0');
	alarmH0 <= (others => '0');
	alarmM1 <= (others => '0');
	alarmM0 <= (others => '0');
elsif optionalSW = '0' and ring = '1' then
    alarmH0 <= clockH0;
    alarmH1 <= clockH1;
    alarmM0 <= clockM0;
    alarmM1 <= clockM1;
	ring <= '0';
	alarmH0 <= alarmH0 + 1;
	if alarmH0 = "1001" then
		alarmm0 <= (others => '0');
		alarmm1 <= alarmm1 + 1;
		if alarmm1 = "0101" then
			alarmm1 <= (others => '0');
			alarmh0 <= alarmh0 + 1;
			if alarmh0 = "1001" then
				alarmh0 <= (others => '0');
				alarmh1 <= sh1 + 1;
				if alarmh1 = "0100" then
					if(alarmh1 = "0010" and alarmh0 = "0011") then
						alarmh1 <= (others => '0');
						alarmh0 <= (others => '0');
					end if;
				end if;
			end if;
        end if;
    end if;
		
elsif clk = '0' and clk'event then
	case state is
		when "00" => 
            if(alarmH1 = clockH1 and alarmH0 = clockH0 and alarmM1 = clockM1 and alarmM0 = clockM0) then
                ring <= '1';
				end if;
			if(adjSW = '0') then
				alrcnt <= alrcnt + 1;
				if(alrcnt = alrtwoSec)then
					nextstate <= "01";
					alrcnt<= (others => '0');
				end if;
			end if;
			
		when "01" =>
-- increase hour
			ring <= '0';
			aeditingFlag <= '1';
			if(upSW = '0') then
				if aCNT > aaSec + ahalfSec then
                aupspeed <= aSecdiv4;
                end if;
			else 
				aupspeed <= ahalfSec;
				aCNT <= aCNT + 1;
			end if;
			
			atemp <= atemp + 1;
			if(atemp > aupspeed) then
				atemp <= (others => '0');

					if(alarmh0 + 1 > "1001") then
  
						case alarmh1 is
							when "0001" =>
								if(alarmh0 +1 > "1100") then
									alarmh1 <= (others => '0');
									alarmh0 <= (others => '0');

								else
									alarmh1 <= alarmh1 + 1;
									alarmh0 <= alarmh0 - "1001";
								end if;
							when "0010" =>
							
								alarmh1 <= (others => '0');
								alarmh0 <= (others => '0');
							when others =>
								alarmh1 <= alarmh1 + 1;
								alarmh0 <= alarmh0 - "1001";
						end case;

					elsif(alarmh0 + 1 > "0011") then
						if(alarmh1 = "0010") then
							alarmh1 <= (others => '0');
							alarmh0 <= (others => '0');
						else
							alarmh0 <= alarmh0 + 1;
						end if;
					else
						alarmh0 <= alarmh0 + 1;
					end if;

			else
				atemp <= ahalfsec - 1;
				aCNT <= (others => '0');
			end if;

				if(adjSW = '0') then         
					aADJCNT <= aADJCNT + 1;
					if(aADJCNT = alrtwoSec) then
						nextstate <= "00";
						atemp <= ahalfsec - 1;
						aADJCNT <= (others => '0');
					else
						nextstate <= state;
					end if;

				else
					aADJCNT <= (others => '0');
					nextstate <= state;
				end if;

				areadingCount <= areadingCount + 1;
				if(areadingCount = secdiv4) THEN
					areadingCount <= (others => '0');
					if(modeSW = '0') then
						nextstate <= "10";
						atemp <= ahalfsec - 1;
						aREADINGCouNT<= (others => '0');
					else 
                        nextstate <= state;

                    end if;
                end if;


		when "10" =>
			aeditingFlag <= '1';
			-- increase minute
			ring <= '0';
			if(upSW = '0') then
				if aCNT > asec + ahalfSec then
					aupspeed <= aSecdiv4;
				else 								
					aupspeed <= ahalfsec;
					aCNT <= aCNT + 1;
				end if;
			
				atemp <= atemp + 1;
			
				if(atemp > aupspeed) then
					atemp <= (others => '0');
					if(alarmm0 + 1 > "1001") then
 
						case alarmm1 is
							when "0101" =>
								alarmm1 <= (others => '0');
								alarmm0 <= (others => '0');
							when others =>
								alarmm1 <= alarmm1 + 1;
								alarmm0 <= alarmm0 - "1001";
						end case;

					else
						alarmm0 <= alarmm0 + 1;
					end if;
				end if;
		
			else
				atemp <= ahalfsec - 1;
				aCNT <= (others => '0');
			end if;
		
			if(adjSW = '0') then         
				aADJCNT <= aADJCNT + 1;
				if(aADJCNT = alrtwoSec) then
					nextstate <= "00";
					atemp <= (others => '0');
                    ADJCNT <= (others => '0');
                end if;
			
		else
			aADJCNT <= (others => '0');
			nextstate <= state;
		end if;
		
		areadingCount <= areadingCount + 1;
		if(areadingCount = asecdiv4) then
			areadingCount <= (others => '0');
			if(modeSW = '0') then
				nextstate <= "11";
				atemp <= ahalfsec - 1;
				ADJCNT<= (others => '0');
			else 
				nextstate <= state;
			end if;
        END IF;
    end case;
end if;
end process;

end BEHAVE;
