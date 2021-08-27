-- ++++++++++++++++++++++++++++++++++++++SELECT_ABFRAGE_QUERYS+++++++++++++++++++++++++++++++++++++++++++++++
/*
SELECT spalte FROM tabelle WHERE wert = straßenname ;
0: SELECT * FROM angebote WHERE  = x ; 
xxx					0: "";
*/
-- 1)-----ANGEBOTE------------------------------------------------------------
Angebot_ID:				0: SELECT * FROM angebote WHERE Angebot_ID = x ;
standort_id 				1: SELECT * FROM standort WHERE standort_id = x ;
Ansprechpartner_ID			2: "";
bezeichnung				3: SELECT * FROM angebote WHERE bezeichnung = x ;
abw. Einsatzort 			4: "";
AnforderungenAllg    			5: SELECT * FROM angebote WHERE AnforderungenAllg = x ;
AnforderungDetails			6: "";
Art					7: SELECT * FROM angebote WHERE Art = x 
Fachrichtung				8: SELECT * FROM angebote WHERE Fachrichtung = x ;
Web					9: "";
Bewerbungsform				10: "";
AusgeschriebenAm			11: SELECT * FROM angebote WHERE AusgeschriebenAm = x ;
Start					12: "";
nichtMehrGueltig			13: "";
eingetragenAm				14: "";
EingetragenVon				15: "";
Anspp._Anspp._ID			16: "";
Ansppp_st_ID				17: "";

-- 2)-----STANDORT-------------------------------------------------------------

standort_id 				0: SELECT * FROM angebote WHERE standort_id = x ; 
Firma_ID				1: SELECT * FROM firma WHERE Firma_ID = x ;
Ersteintrag				2: "";
Zentrale				3: "";
PLZ					4: SELECT * FROM standort WHERE PLZ = x ;
Strasse					5: "";
ORT					6: SELECT * FROM standort WHERE Ort = x ; -- CRT = ORT?
TelefonStandort				7: "";
Mitarbeiter				8: "";
eingetragenAm				9: "";
EingetragenVon				10: "";
sLat					11: "";	   -- was soll da passieren?
sLon					12:  "";   -- was soll da passieren?
-- 3)-----FIRMA------------------------------------------------------------------

Firma_id				0: SELECT * FROM standort WHERE Firma_ID = x ; -- Oben 1: 
Name					1: SELECT * FROM firma WHERE name = x ;
Rechtsform				2: "";
Plz_Zen = PLZ				3: SELECT * FROM standort WHERE PLZ = x ;
ORT_Zentrale				4: SELECT * FROM standort WHERE Ort = x ; --CRT oder ORT?
Website		 			5: "";
Inhouse_IT				6: "";
Branche					7: "";
personalvermittler  			8: "";
eingetragenAm				9: "";
EingetragenVon				10:"";

-- 4)-----Ansprechpartner------------------------------------------------------------------

Ansprechp._id 				0: SELECT * FROM angebote WHERE Ansprechpartner_Ansprechpartner_ID = x ;
Standort_ID				1: "";
Anrede					2: "";
Name					3: "";
Vorname					4: "";
Telefon					5: "";
email					6: "";
Funktion				7: "";
socialMedia				8: "";
eingetragenAm				9: "";
eingetragenVon				10: "";
stdt_Stdt_id				11: SELECT * FROM standort WHERE standort_ID = x ;	  
