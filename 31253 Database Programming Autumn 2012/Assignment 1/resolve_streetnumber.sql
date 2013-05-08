CREATE OR REPLACE FUNCTION resolve_streetnumber
  ( address_in IN varchar2 )
  RETURN varchar2
IS
  streetnumber varchar2(10) := '';
  streetnumberpattern varchar(200) := '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2} ';
  fulladdresspattern varchar(260) := '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2}([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd)';
  
  cursor c1 is
    select substr(regexp_substr(STREET1, streetnumberpattern),1,10)
    from helens_data
    where street1 = address_in
    and   regexp_like(STREET1, fulladdresspattern)
    and   length(regexp_substr(STREET1, streetnumberpattern)) < 11;
  
BEGIN

open c1;
fetch c1 into streetnumber;
if c1%notfound then
    streetnumber := '';
end if;
close c1;

RETURN streetnumber;

EXCEPTION
WHEN OTHERS THEN
    raise_application_error(20001,'An error was encountered - '||SQLCODE||' -ERROR '||SQLERRM);
END;