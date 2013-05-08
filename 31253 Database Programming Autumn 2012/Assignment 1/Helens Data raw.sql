-- Database version info
SELECT BANNER FROM V$VERSION;

-- New tables: view
select * from dbp_clients;
select * from dbp_client_exceptions;

-- New tables: clear
TRUNCATE TABLE dbp_clients;
TRUNCATE TABLE dbp_client_exceptions;

DECLARE
BEGIN
clean_helens_data;
END;

-- Function proofs
SELECT id, fname, surname, company, street1, suburb, resolve_corner(street1), resolve_pobox(street1), resolve_streetnumber(street1), resolve_streetname(street1), resolve_postcode(suburb)
FROM HELENS_DATA;
        
--Good postcodes conversion        
SELECT  postcode,
        locality
FROM    DBP_POSTCODE
WHERE   DBP_POSTCODE.locality IN (
        SELECT    DBP_POSTCODE.locality
        FROM      DBP_POSTCODE
        GROUP BY  DBP_POSTCODE.locality
        HAVING    count(DBP_POSTCODE.locality) = 1
        );

-- Regular Expressions for numbered street addresses
SELECT street1,
      regexp_substr(STREET1, '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2} ') "Street Number",
      regexp_substr(STREET1, '([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd)') "Street Name",
      regexp_substr(STREET1, '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2}([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd)') "Full Address"
FROM helens_data;
WHERE regexp_like(STREET1, '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2}([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd)');