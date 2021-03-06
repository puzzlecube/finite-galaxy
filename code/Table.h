// Table.h

#ifndef TABLE_H_
#define TABLE_H_

#include "Colour.h"
#include "Point.h"

#include <string>
#include <vector>

class Font;
class Rectangle;



// Helper class for drawing text formatted in a table, where each column of the
// table is aligned left, right, or centred. This also handles spacing in
// between table rows, underlines, selection highlights, etc.
class Table {
public:
  enum Align {LEFT = 0, CENTRE = 1, RIGHT = 2};
  
  
public:
  Table();
  
  // Set the column positions. If no columns are set, the Table will draw a
  // list (one column of text, left aligned).
  void Clear();
  void AddColumn(int x, Align align);
  
  // Set the font size. Default is 14 pixels.
  void SetFontSize(int size);
  // Set the row height. Default is 20 pixels.
  void SetRowHeight(int height);
  // Set the width of the highlight area. If the underline has not been set,
  // this will also set the width of the underline.
  void SetHighlight(int startX, int endX);
  // Set the X range of the underline. If the highlight has not been set, this
  // will also set the width of the highlight.
  void SetUnderline(int startX, int endX);
  
  // Begin drawing at the given position. Each time text is drawn, it fills a
  // new column until all columns have been filled. Then, the Y position is
  // increased based on the row height, and a new row begins.
  void DrawAt(const Point &point) const;
  
  // Set the colour for drawing text and underlines.
  void SetColour(const Colour &colour) const;
  
  // Advance to the next field without drawing anything.
  void Advance(int fields = 1) const;
  
  // Draw a single text field, and move on to the next one.
  void Draw(const std::string &text) const;
  // If a colour is given, this field is drawn using that colour, but the
  // previously set colour will be used for future fields.
  void Draw(const std::string &text, const Colour &colour) const;
  void Draw(double value) const;
  void Draw(double value, const Colour &colour) const;
  
  // Draw an underline under the text for the current row.
  void DrawUnderline() const;
  void DrawUnderline(const Colour &colour) const;
  
  // Highlight the current row.
  void DrawHighlight() const;
  void DrawHighlight(const Colour &colour) const;
  
  // Shift the draw position down by the given amount. This usually should not
  // be called in the middle of a row, or the fields will not line up.
  void DrawGap(int y) const;
  
  // Get the point that should be passed to DrawAt() to start the next row at
  // the given location.
  Point GetPoint();
  
  // Get the centre and size of the current row. This can be used to define
  // what screen region constitutes a mouse click on this particular row.
  Point GetCentrePoint() const;
  Point GetRowSize() const;
  Rectangle GetRowBounds() const;
  
  
private:
  // Starting position for drawing a column is:
  // point + Point(offset + align * font.Width(text), 0.)
  // So, "align" will either be 0, -.5, or -1.
  class Column {
  public:
    Column();
    Column(double offset, double align);
    
    double offset;
    double align;
  };
  
  
private:
  mutable Point point;
  mutable std::vector<Column>::const_iterator it;
  mutable Colour colour;
  
  const Font *font;
  Point rowSize;
  Point centre;
  Point lineSize;
  Point lineOff;
  
  std::vector<Column> columns;
};



#endif
