<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="html" indent="yes"/>

<xsl:template match="/">
  <html>
    <body>
      <table border="1" width="80%">
        <tr>
          <th>Code</th>
          <th>Name</th>
          <th>Description</th>
        </tr>
        <xsl:apply-templates/>
      </table>
    </body>

  </html>	
</xsl:template>

<xsl:template match="entry">
  <tr><xsl:apply-templates/></tr>
</xsl:template>

<xsl:template match="code">
  <td><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="name">
  <td><xsl:apply-templates/></td>
</xsl:template>

<xsl:template match="description">
  <td><xsl:apply-templates/></td>
</xsl:template>

</xsl:stylesheet>
