<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"/>

<xsl:template match="location">
	<br />
	<table>
		<tr>
			<td width="150px">Latitude:</td>
			<td><xsl:value-of select="latitude"/></td>
		</tr>
		<tr>
			<td>Longitude:</td>
			<td><xsl:value-of select="longitude"/></td>
		</tr>
	</table>
	<br />
	
	<xsl:element name="iframe">
		<xsl:attribute name="width">
			<xsl:text>680</xsl:text>
		</xsl:attribute>
		<xsl:attribute name="height">
			<xsl:text>480</xsl:text>
		</xsl:attribute>
		<xsl:attribute name="frameborder">
			<xsl:text>0</xsl:text>
		</xsl:attribute>
		<xsl:attribute name="scrolling">
			<xsl:text>no</xsl:text>
		</xsl:attribute>
		<xsl:attribute name="marginheight">
			<xsl:text>0</xsl:text>
		</xsl:attribute>
		<xsl:attribute name="marginwidth">
			<xsl:text>0</xsl:text>
		</xsl:attribute>
		
		<xsl:attribute name="src">
			<xsl:text>http://maps.google.com/maps?q=</xsl:text>
			<xsl:value-of select="latitude"/>
			<xsl:text>, </xsl:text>
			<xsl:value-of select="longitude"/>
			<xsl:text>&amp;ie=UTF8&amp;t=h&amp;z=10&amp;ll=</xsl:text>
			<xsl:value-of select="latitude"/>
			<xsl:text>, </xsl:text>
			<xsl:value-of select="longitude"/>
			<xsl:text>&amp;output=embed</xsl:text>
		</xsl:attribute>
	</xsl:element>
</xsl:template>

</xsl:stylesheet>
