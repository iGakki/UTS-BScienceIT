create or replace
PACKAGE Assignment2 AS  -- Package specification by David Evans davidjsevans@gmail.com --
/*  **RM16_forecast** procedure by davidjsevans@gmail.com
    Purpose: to trigger a forecast covering the desired forecast period (set in 
      the "parameter" table)
    Input: v_nem_rm16 table
    Output: local_rm16 table */
    PROCEDURE RM16_forecast;

/*  **insert_forecast** procedure by davidjsevans@gmail.com
    Purpose: to control the generation and insertion of all forecasts for the 
      desired forecast period (set in the "parameter" table)
    Input: day
    Output: rows inserted into local_RM16 */
    PROCEDURE insert_forecast ( day_in DATE );
  
/*  **insert_forecast_regular** procedure by davidjsevans@gmail.com
    Purpose: to generate a one-day regular forecast and insert it into the local_RM16 table
    Input: day
    Output: rows inserted into local_RM16 */
    PROCEDURE insert_forecast_regular ( day_in DATE );

/*  **insert_forecast_holiday** procedure by davidjsevans@gmail.com
    Purpose: to generate a one-day holiday forecast and insert it into the local_RM16 table
    Input: day
    Output: rows inserted into local_RM16 */
    PROCEDURE insert_forecast_holiday ( day_in DATE );
    
/*  **day_of_week** function by davidjsevans@gmail.com
    Purpose: to facilitate forecasting based on the same days of other weeks
    Input: date
    Output: day of the week: 1 Mon, 2 Tues ... 7 Sun */
    FUNCTION day_of_week ( date_in DATE ) RETURN CHAR;
    
/*  **time_stamp** function by davidjsevans@gmail.com
    Purpose: to format dates uniformly for the purpose of timestamping
    Input: date
    Output: characters representing the formatted date */
    FUNCTION time_stamp ( date_in DATE ) RETURN VARCHAR2;
    
/*  **format_date** function by davidjsevans@gmail.com
    Purpose: Constant values are stored in the parameter table, so that they can 
      be changed without changing the program.  This function retrieves them for use.
    Input: name of constant
    Output: value of constant as VARCHAR2 */
    FUNCTION constant ( name_in VARCHAR2 ) RETURN VARCHAR2;
END Assignment2;

/* Initialisation scripts by davidjsevans@gmail.com:
The following scripts will create and populate the tables required to run the Assignment2 program.

To create the **PARAMETER** table and populate with default parameters:
CREATE TABLE PARAMETER
(
  "KIND"        VARCHAR2(25 BYTE),
  "CODE"        VARCHAR2(25 BYTE),
  "VALUE"       VARCHAR2(255 BYTE),
  "DESCRIPTION" VARCHAR2(255 BYTE),
  "ACTIVE"      VARCHAR2(1 BYTE),
  "AUDIT_DATE" DATE DEFAULT sysdate
);
INSERT ALL
   INTO PARAMETER (KIND,CODE,VALUE,DESCRIPTION,ACTIVE) VALUES ('EMAIL_ADDRESS','ASS2_RECIPIENT','laurie@laurieb.com.au','The destination for the email message for Assignment2','Y')
   INTO PARAMETER (KIND,CODE,VALUE,DESCRIPTION,ACTIVE) VALUES ('CONSTANT','NO_DAYS_TO_FORECAST','14','The number of days to forecast for Assignment2','Y')
   INTO PARAMETER (KIND,CODE,VALUE,DESCRIPTION,ACTIVE) VALUES ('CONSTANT','DATE_FORMAT','DD/MON/YY HH24:MI:SS','The date format for logging for Assignment2','Y')
SELECT * FROM dual;

To create the **LOCAL_RM16** table for forecasts to be inserted into:
CREATE TABLE LOCAL_RM16
(
  COMPANY_CODE        VARCHAR2(25 BYTE),
  SETTLEMENT_CASE_ID  NUMBER,
  SETTLEMENT_RUN_ID   NUMBER,
  STATEMENT_TYPE      VARCHAR2(25 BYTE),
  TNI                 VARCHAR2(25 BYTE),
  METERTYPE           VARCHAR2(25 BYTE),
  FRMP                VARCHAR2(25 BYTE),
  LR                  VARCHAR2(25 BYTE),
  MDP                 VARCHAR2(25 BYTE),
  CHANGE_DATE         DATE,
  DAY                 DATE,
  TRANSACTION_ID      VARCHAR2(25 BYTE),
  HH                  NUMBER,
  VOLUME              NUMBER
); */


create or replace
PACKAGE BODY Assignment2 AS  -- Package body by David Evans davidjsevans@gmail.com --

/*  **RM16_forecast** procedure by davidjsevans@gmail.com
    Purpose: to trigger a forecast covering the desired forecast period (set in 
      the "parameter" table)
    Input: v_nem_rm16 table
    Output: local_rm16 table */
PROCEDURE RM16_forecast IS
  no_days_to_forecast NUMBER;
  BEGIN
    no_days_to_forecast := to_number( constant ( 'NO_DAYS_TO_FORECAST' ) );
    common.log( '[' || time_stamp(sysdate) || '] BEGIN: Forecasting for ' || sysdate 
      || ' to ' || (sysdate + no_days_to_forecast) || ' started.' );
    DELETE FROM local_rm16;
    FOR day_counter IN 1..no_days_to_forecast
    LOOP
      Assignment2.insert_forecast( (trunc(sysdate) + day_counter) );
    END LOOP;
    COMMIT;
    common.log( '[' || time_stamp(sysdate) || '] END: Forecasting for ' || sysdate 
      || ' to ' || (sysdate + no_days_to_forecast) || ' complete.' );
END RM16_forecast;

/*  **insert_forecast** procedure by davidjsevans@gmail.com
    Purpose: to control the generation and insertion of all forecasts for the 
      desired forecast period (set in the "parameter" table)
    Input: day
    Output: rows inserted into local_RM16 */
PROCEDURE insert_forecast ( day_in DATE ) IS -- put the test in here holiday/weekday
  holiday NUMBER;
  BEGIN
    SELECT COUNT(holiday_date) INTO holiday
    FROM dbp_holiday
    WHERE holiday_date = (day_in);
    CASE holiday
      -- When day_in is not a holiday, then...
      WHEN 0 THEN insert_forecast_regular ( day_in ); 
      -- When day_in is a holiday, then...
      ELSE insert_forecast_holiday ( day_in );
    END CASE;
  EXCEPTION WHEN OTHERS THEN
    common.log( 'Error occured in insert_forecast with '||SQLCODE||' -ERROR '||SQLERRM );
    ROLLBACK;
END insert_forecast;

/*  **insert_forecast_regular** procedure by davidjsevans@gmail.com
    Purpose: to generate a one-day regular forecast and insert it into the local_RM16 table
    Input: day
    Output: rows inserted into local_RM16 */
PROCEDURE insert_forecast_regular ( day_in DATE ) IS
  BEGIN
    FOR hh_counter IN 1..48
      LOOP
        INSERT INTO local_RM16 ( statement_type, frmp, lr, tni, change_date, day, hh, volume )
        SELECT 'FORECAST' as statement_type,
               r.frmp,
               r.lr,
               r.tni,
               sysdate as change_date,
               day_in as day,
               hh_counter as hh,
               round( avg( r.volume ), 6 ) as volume
        FROM v_nem_rm16 r
        LEFT JOIN dbp_holiday h ON r.day = h.holiday_date
        WHERE day_of_week ( r.day ) = day_of_week( day_in ) -- Bus Rule: Forecast for same days of the week
              AND hh = hh_counter -- Bus Rule: Forecast for same half-hour of the day
              AND h.holiday_date IS NULL -- Bus Rule: Exclude holidays
        GROUP BY frmp, lr, tni, day_in, day_of_week( day_in ), hh_counter;
      END LOOP;
  EXCEPTION WHEN OTHERS THEN
    common.log( 'Error occured in insert_forecast with '||SQLCODE||' -ERROR '||SQLERRM );
    ROLLBACK;
END insert_forecast_regular;

/*  **insert_forecast_holiday** procedure by davidjsevans@gmail.com
    Purpose: to generate a one-day holiday forecast and insert it into the local_RM16 table
    Input: day
    Output: rows inserted into local_RM16 */
PROCEDURE insert_forecast_holiday ( day_in DATE ) IS
BEGIN
  FOR hh_counter IN 1..48
    LOOP
      -- For TNIs *with* past data for holidays...
      INSERT INTO local_RM16 ( statement_type, frmp, lr, tni, change_date, day, hh, volume )
      SELECT 'FORECAST' as statement_type,
             r.frmp,
             r.lr,
             r.tni,
             sysdate as change_date,
             day_in as day,
             hh_counter as hh,
             round( avg( r.volume ), 6 ) as volume
      FROM v_nem_rm16 r
      LEFT JOIN dbp_holiday h ON r.day = h.holiday_date
      WHERE hh = hh_counter -- Bus Rule: Forecast for same half-hour of the day
            AND h.holiday_date IS NOT NULL -- Bus Rule: Forecast for other holidays
      GROUP BY frmp, lr, tni, day_in, day_of_week( day_in ), hh_counter;
      
      -- For TNIs *without* past data for holidays...
      INSERT INTO local_RM16 ( statement_type, frmp, lr, tni, change_date, day, hh, volume )
      SELECT 'FORECAST' as statement_type,
             r.frmp,
             r.lr,
             r.tni,
             sysdate as change_date,
             day_in as day,
             hh_counter as hh,
             round( avg( r.volume ), 6 ) as volume
      FROM v_nem_rm16 r
      LEFT JOIN dbp_holiday h ON r.day = h.holiday_date
      WHERE hh = hh_counter -- Bus Rule: Forecast for same half-hour of the day
            AND h.holiday_date IS NULL -- Bus Rule: Exclude holidays
            AND day_of_week ( r.day ) = '7' -- Bus Rule: Use Sundays instead
            AND tni NOT IN (SELECT DISTINCT r.tni FROM v_nem_rm16 r LEFT JOIN dbp_holiday h ON h.holiday_date = r.day WHERE h.holiday_date IS NOT NULL)
      GROUP BY frmp, lr, tni, day_in, day_of_week( day_in ), hh_counter;
    END LOOP;
  EXCEPTION WHEN OTHERS THEN
    common.log( 'Error occured in insert_forecast with '||SQLCODE||' -ERROR '||SQLERRM );
    ROLLBACK;
END insert_forecast_holiday;

/*  **day_of_week** function by davidjsevans@gmail.com
    Purpose: to facilitate forecasting based on the same days of other weeks
    Input: date
    Output: day of the week: 1 Mon, 2 Tues ... 7 Sun */
FUNCTION day_of_week ( date_in DATE ) RETURN CHAR IS
  day_of_week CHAR := to_char(date_in, 'D');
  BEGIN
  RETURN day_of_week;
  EXCEPTION WHEN OTHERS THEN
    common.log( 'Error occured in insert_forecast with '||SQLCODE||' -ERROR '||SQLERRM );
    ROLLBACK;
END day_of_week;

/*  **time_stamp** function by davidjsevans@gmail.com
    Purpose: to format dates uniformly for the purpose of timestamping
    Input: date
    Output: characters representing the formatted date */
FUNCTION time_stamp (date_in DATE ) RETURN VARCHAR2 IS
  formatted_date VARCHAR2(32);
  BEGIN
  formatted_date := to_char( date_in, constant( 'DATE_FORMAT' ) );
  RETURN formatted_date;
  EXCEPTION WHEN OTHERS THEN
    common.log( 'Error occured in insert_forecast with '||SQLCODE||' -ERROR '||SQLERRM );
    RETURN date_in;
END time_stamp;

/*  **format_date** function by davidjsevans@gmail.com
    Purpose: Constant values are stored in the parameter table, so that they can 
      be changed without changing the program.  This function retrieves them for use.
    Input: name of constant
    Output: value of constant as VARCHAR2 */
FUNCTION constant ( name_in VARCHAR2 ) RETURN VARCHAR2 IS
  value_out VARCHAR2(255);
  BEGIN
    SELECT VALUE INTO value_out FROM parameter WHERE KIND = 'CONSTANT' AND code = name_in;
  RETURN value_out;
  EXCEPTION WHEN OTHERS THEN
    common.log( 'Error occured in insert_forecast with '||SQLCODE||' -ERROR '||SQLERRM );
    ROLLBACK;
  END constant;

END Assignment2;