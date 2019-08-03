Library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity segment is
port(
    rst : in std_logic;
    nextMode	    : out std_logic_vector(1 downto 0);
    src_TIME_H1               : in std_logic_vector(3 downto 0);
    src_TIME_H0               : in std_logic_vector(3 downto 0);
    src_TIME_M1               : in std_logic_vector(3 downto 0);
    src_TIME_M0               : in std_logic_vector(3 downto 0);
    src_TIME_S1               : in std_logic_vector(3 downto 0);
    src_TIME_S0               : in std_logic_vector(3 downto 0);
    HEX0               : out std_logic_vector(7 downto 0);
    HEX1               : out std_logic_vector(7 downto 0);
    HEX2               : out std_logic_vector(7 downto 0);
    HEX3               : out std_logic_vector(7 downto 0);
    HEX4               : out std_logic_vector(7 downto 0);
    HEX5               : out std_logic_vector(7 downto 0)
    );
end segment;

architecture behave of segment is
