#ifndef VIEW_INFO
#define VIEW_INFO

#include "view.h"

/*! View for simple text message output. */

class ViewInfo : public View
{
public:
    ViewInfo(void);
    virtual void setText(std::string text);
    virtual void setLabelClose(std::string label);;
    virtual void setCall(call_t call);
    virtual void draw(void) override;
    virtual call_t keypress(int& key) override;

protected:
    std::string text;
    std::string label_close;
    int close_offset_x = 0;
    int close_offset_y = 0;
    constexpr static int text_offset_x = 2;
    constexpr static int text_offset_y = 3;
};

#endif // VIEW_INFO
