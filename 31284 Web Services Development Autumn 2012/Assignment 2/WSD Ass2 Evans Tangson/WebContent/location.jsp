<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page import="client.*"%>
<%@page import="javax.xml.transform.stream.*"%>
<%@page import="javax.xml.transform.*"%>
<%@page import="java.math.BigDecimal"%>
<%@page import="java.text.DecimalFormat"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<style type="text/css" media="all">
		@import "style.css";
	</style>
	<title>Location Web Application</title>
</head>

<body>
<%!
DecimalFormat df = new DecimalFormat("#.##");

void DistanceClient(BigDecimal fromlat, BigDecimal fromlong, BigDecimal tolat, 
		BigDecimal tolong, String units, JspWriter out) {
	// Instantiate the generated Service
	Distance distance = new Distance();
	        
	// Get the port using port getter method generated in Distance
	DistancePortType distancePort = distance.getDistancePort();
	
	// Build the required new objects with the ObjectFactory...
	ObjectFactory objectFactory = new ObjectFactory();
	
	// ...The from coordinates 
	CoordinateType from = objectFactory.createCoordinateType();
	from.setLatitude(fromlat);
	from.setLongitude(fromlong);
	
	// ...The to coordinates
	CoordinateType to = objectFactory.createCoordinateType();
	to.setLatitude(tolat);
	to.setLongitude(tolong);
	
	// ...The request object
	GetDistanceRequestType distanceReq = objectFactory.createGetDistanceRequestType();
	distanceReq.setSourceLocation(from);
	distanceReq.setDestinationLocation(to);
	distanceReq.setUnits(units);
		
	// Call the web service to carry out the calculation and store the response
	GetDistanceResponseType distanceResp = distancePort.getDistance(distanceReq);	

	// Print the response information
	try {
		if ( distanceResp.isValid() ) {
			out.println("<p>Distance from origin to destination is " 
				+ df.format(distanceResp.getDistance().doubleValue()) + " " + units + ".</p>");
			out.println("<p>Bearing from origin to destination is " 
				+ df.format(distanceResp.getBearing().doubleValue()) + " degrees.</p>");
		}
	}
	catch (Exception e) { e.printStackTrace(); }
}
%>

<h1>Location Web Application</h1>

<p>This web application uses JSP, and XSLT to retrieve results from the 'location'
SOAP Web Service.<br>
The following links are examples which invoke the remote method.</p>


<a href="location.jsp?fromlat=90&fromlong=14&tolat=19&tolong=126&units=kilometres">From 90, 14 To 19, 126 In Kilometres</a><br>
<a href="location.jsp?fromlat=51&fromlong=140&tolat=14&tolong=98&units=miles">From 51, 140 To 14, 98 In Miles</a><br>
<a href="location.jsp?fromlat=18&fromlong=21&tolat=82&tolong=22&units=kilometres">From 18, 21 To 82, 22 in Kilometres</a><br><br>

Alternatively the following form will generate a QueryString to invoke the remote method.<br>

		  <form method="GET" action="location.jsp">

		    <p>Origin latitude:
			<input type="text" name="fromlat"/></p>

		    <p>Origin longitude:
			<input type="text" name="fromlong"/></p>

		    <p>Destination latitude:
			<input type="text" name="tolat"/></p>

		    <p>Destination longitude:
			<input type="text" name="tolong"/></p>

			<p>
			Units:
			<select name="units">
			  <option value="kilometres">kilometres</option>
			  <option value="miles">miles</option>
			</select>
			</p>

			<p>
			<input type="submit" value="Calculate Distance &amp; Bearing" />
			</p>
		  </form>
		  <br>

<%
if(request.getParameter("fromlat") != null && request.getParameter("fromlong") != null 
&& request.getParameter("tolat") != null && request.getParameter("tolong") != null 
&& request.getParameter("units").matches( "(miles|kilometres)" ) ) {
	BigDecimal fromlat = new BigDecimal(request.getParameter("fromlat"));
	BigDecimal fromlong = new BigDecimal(request.getParameter("fromlong"));
	BigDecimal tolat = new BigDecimal(request.getParameter("tolat"));
	BigDecimal tolong = new BigDecimal(request.getParameter("tolong"));
	String units = request.getParameter("units");
	
	DistanceClient(fromlat, fromlong, tolat, tolong, units, out);
}
%>
</body>
</html>