<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"/>

<xsl:template match="entry">
		<xsl:attribute name="value"><xsl:apply-templates select="code"/></xsl:attribute>
   		<xsl:apply-templates select="name"/> (
   		<xsl:apply-templates select="description"/> )
</xsl:template>

</xsl:stylesheet>
