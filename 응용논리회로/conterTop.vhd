
Library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counterTop is
end counterTop;

architecture behave of counterTop is
component counter is 
port(
	clk			    : in std_logic;
	rst 			: in std_logic;
    adjSW			: in std_logic;
    modeSW          : in std_logic;
    upSW            : in std_logic;
curMode : in std_logic_vector(1 downto 0);
nextMode : out std_logic_vector(1 downto 0);
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
end component;

signal	clk : std_logic :='0';
signal rst: std_logic := '1';
signal adjSW: std_logic := '1';
signal modeSW: std_logic := '1';
signal upSW: std_logic := '1';
signal curMode : std_logic_vector(1 downto 0) := "00";
signal nextMode : std_logic_vector(1 downto 0) := "00";
signal    src_TIME_H1               : std_logic_vector(3 downto 0) := "0000";
signal    src_TIME_H0               : std_logic_vector(3 downto 0) := "0000";
signal    src_TIME_M1               : std_logic_vector(3 downto 0) := "0000";
signal    src_TIME_M0               : std_logic_vector(3 downto 0) := "0000";
signal    src_TIME_S1               : std_logic_vector(3 downto 0) := "0000";
signal	 src_TIME_S0               : std_logic_vector(3 downto 0) := "0000";
signal    rst_TIME_H1               :  std_logic_vector(3 downto 0) := "0000";
signal    rst_TIME_H0               : std_logic_vector(3 downto 0) := "0000";
signal    rst_TIME_M1               : std_logic_vector(3 downto 0) := "0000";
signal    rst_TIME_M0               : std_logic_vector(3 downto 0) := "0000";
signal    rst_TIME_S1               : std_logic_vector(3 downto 0) := "0000";
signal	rst_TIME_S0               : std_logic_vector(3 downto 0) := "0000";

begin

count : counter port map(
	 clk		=> clk,
	rst		=> rst,
adjSW => adjSW,
modeSW => modeSW,
upSW => upSW,
curMode => curMode,
nextMode => nextMode,
    src_TIME_H1         => src_time_h1,
    src_TIME_H0         => src_time_h0,
    src_TIME_M1         => src_time_m1,
    src_TIME_m0         => src_time_m0,
    src_TIME_S1          => src_time_s1,
    src_TIME_S0      =>src_time_s0,
    rst_TIME_H1            => rst_time_h1,
    rst_TIME_H0            =>rst_time_H0,
    rst_TIME_M1            => rst_time_M1,
    rst_TIME_M0             => rst_time_m0,
    rst_TIME_S1             => rst_time_s1,
	rst_TIME_S0         =>rst_time_s0
);

RST <= '0', '1' after 1ns;
upSW <= '0';
process
begin
modeSW <= '0', '1' after 1ns;
wait for 30ns;
end process;

process
begin
adjSW <= not(adjSW);
wait for 100ns;
end process;

Process
begin
Clk <= not(clk);
 wait for 2ns;
curMode <= nextMode;
end process;

end behave;
