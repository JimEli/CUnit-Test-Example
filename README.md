# Example Use of CUnit Test Framework

Example program from CUnit Test Framework inside MSVC 2017 Community Edition.

Pre-compiled CUnit framework sorced from here:
  https://sourceforge.net/projects/cunit-msvc/files/
  
After running installer, follow the included directions:

From Visual Studio, you can reference CUnit libraries using the CUnit property sheet %CUnitRoot%\CUnit.props. In your Visual Studio project file, an XML file ending in .vcxproj, add the following section:

  <ImportGroup Label="PropertySheets">
    <Import Project="$(CUnitRoot)\CUnit.props" />
  </ImportGroup>

