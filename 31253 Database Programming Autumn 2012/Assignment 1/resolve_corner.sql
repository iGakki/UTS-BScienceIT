CREATE OR REPLACE FUNCTION resolve_corner
  ( address_in IN varchar2 )
  RETURN varchar2
IS
  streetname varchar2(35) := '';
  streetnamepattern varchar2(160) := '([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd|Cl(ose)?)';
  
  cursor c1 is
    select regexp_substr(STREET1, 'C(n|orne)r '||streetnamepattern||' \& '||streetnamepattern)
    from helens_data
    where street1 = address_in;
  
BEGIN

open c1;
fetch c1 into streetname;
if c1%notfound then
    streetname := '';
end if;
close c1;

RETURN streetname;

EXCEPTION
WHEN OTHERS THEN
    raise_application_error(20001,'An error was encountered - '||SQLCODE||' -ERROR '||SQLERRM);
END;