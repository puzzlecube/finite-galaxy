// WrappedText.h

#ifndef WRAPPED_TEXT_H_
#define WRAPPED_TEXT_H_

#include "Point.h"

#include <string>
#include <vector>

class Colour;
class Font;



// Class for calculating word positions in wrapped text. You can specify various
// parameters of the formatting, including text alignment.
class WrappedText {
public:
  WrappedText();
  explicit WrappedText(const Font &font);
  
  // Set the alignment mode.
  enum Align {LEFT, CENTRE, RIGHT, JUSTIFIED};
  Align Alignment() const;
  void SetAlignment(Align align);
  
  // Set the wrap width. This does not include any margins.
  int WrapWidth() const;
  void SetWrapWidth(int width);
  
  // Set the font to use. This will also set sensible defaults for the tab
  // width, line height, and paragraph break. You must specify the wrap width
  // and the alignment separately.
  void SetFont(const Font &font);
  
  // Set the width in pixels of a single '\t' character.
  int TabWidth() const;
  void SetTabWidth(int width);
  
  // Set the height in pixels of one line of text within a paragraph.
  int LineHeight() const;
  void SetLineHeight(int height);
  
  // Set the extra spacing in pixels to be added in between paragraphs.
  int ParagraphBreak() const;
  void SetParagraphBreak(int height);
  
  // Wrap the given text. Use Draw() to draw it.
  void Wrap(const std::string &str);
  void Wrap(const char *str);
  
  // Get the height of the wrapped text.
  int Height() const;
  
  // Draw the text.
  void Draw(const Point &topLeft, const Colour &colour) const;
  
  
private:
  void SetText(const char *it, size_t length);
  void Wrap();
  void AdjustLine(unsigned &lineBegin, int &lineWidth, bool isEnd);
  int Space(char c) const;
  
  
private:
  // The returned text is a series of words and (x, y) positions:
  class Word {
  public:
    Word();
    
    size_t Index() const;
    Point Pos() const;
    
  private:
    size_t index;
    int x;
    int y;
    
    friend class WrappedText;
  };
  
  
private:
  const Font *font;
  
  int space;
  int wrapWidth;
  int tabWidth;
  int lineHeight;
  int paragraphBreak;
  Align alignment;
  
  std::string text;
  std::vector<Word> words;
  int height;
};



#endif
