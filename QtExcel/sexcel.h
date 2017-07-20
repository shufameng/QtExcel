/**
 * 文件名: sexcel.h
 *
 * SExcel类是一个基于Qt的Excel文档操作类,
 * 该类提供了对Excel的新建,打开,修改,保存等操作.
 *
 * 需要在Qt项目文件中加入:
 * QT       += axcontainer
 *
 * VBA Excel中的对象:
 * - 应用对象(Excel.Application): 打开的Excel应用程序实例.
 *
 * - 工作簿对象(WorkBooks): 包含Excel应用中打开的所有工作簿.
 *
 * - 工作表对象(WorkSheets): 包含工作簿中的所有工作表.
 *
 * - 范围对象(Range): 工作表中的一定范围,可以是一个单元格,也可以是多个单元格.
 *
 * 注意:
 * 1.所有函数中的Row和Column都是从1开始,不是从0开始.
 */


#ifndef SEXCEL_H
#define SEXCEL_H

#include <QObject>
#include <QAxObject>

class SExcel : public QObject
{
    Q_OBJECT

public:
    // 水平对齐方式
    enum HAlignment {
        HAlignCenter = -4108, // xlCenter = -4108
        HAlignLeft = -4131,     // xlLeft = -4131
        HAlignRight = -4152    // xlRight = -4152
    };

    // 垂直对齐方式
    enum VAlignment {
        VAlignCenter = -4108, // xlCenter = -4108
        VAlignTop = -4106,      // xlTop = -4106
        VAlignBottom = -4107    // xlBottom = -4107
    };

    SExcel(QObject *parent = 0);
    virtual ~SExcel();

    // 应用对象
    bool execute();                                             /* 运行Excel应用程序 */
    void quit();                                                   /* 关闭Excel应用程序 */
    inline bool isVisible() const { return mIsVisible; }    /* 获取Excel应用程序窗口是否可见 */
    inline void setVisible(const bool b) { mIsVisible = b; mExcelApp->setProperty("Visible", mIsVisible); } /* 设置Excel应用程序窗口是否可见 */
    inline QString errorString() const { return mErrorString; }     /* 获取Excel应用程序的错误描述 */
    inline bool isExecuted() const { return mIsExecuted; }          /* 获取Excel应用程序是否已经启动 */

    // 工作簿对象
    int workBooksCount();                                      /* 打开的工作簿的总数 */
    void newWorkBook();                                         /* 新建工作簿 */
    void closeWorkBooks();                                      /* 关闭所有工作簿 */
    void saveAsXLS(const QString &filePath);          /* 将活动工作簿保存为后缀名为 xls 的excel文档文件 */
    void saveAsXLSX(const QString &filePath);        /* 将活动工作簿保存为后缀名为 xlsx 的excel文档文件 */
    void open(const QString &filePath);                    /* 在新的工作簿中打开文件 */
    void save();                                                         /* 保存活动工作簿的修改 */

    // 工作表对象
    int workSheetsCount();                                                                 /* 活动工作簿中的工作表总数 */
    bool setActiveWorkSheetName(const QString &name);                   /* 设置当前工作表的名称 */
    bool setWorkSheetName(const int index, const QString &name);    /* 设置活动工作簿中第index个工作表的名称 */
    bool setActiveWorkSheet(const int index);                                     /* 设置活动工作表 */

    // 范围对象,包含一定范围内的所有单元格
    QAxObject *getRange(const QString &name);                                                                                                                             /* 获取范围对象 */
    QAxObject *getRange(const int startRow, const int startColumn, const int endRow, const int endColumn);                                    /* 获取范围对象 */
    void setRangeProperty(const int startRow, const int startColumn, const int endRow, const int endColumn, const QString &propertyName, const QVariant &propertyValue); /* 设置范围单元格的任意属性 */
    void setRangeHAlignment(const int startRow, const int startColumn, const int endRow, const int endColumn, HAlignment align);    /* 设置范围单元格的水平对齐方式 */
    void setRangeVAlignment(const int startRow, const int startColumn, const int endRow, const int endColumn, VAlignment align);    /* 设置范围单元格的垂直对齐方式 */
    void setRangeMergeCells(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b);            /* 设置范围单元格是否合并单元格 */
    void setRangeWrapText(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b);              /* 设置范围单元格是否自动换行 */

    void setRangeFontProperty(const int startRow, const int startColumn, const int endRow, const int endColumn, const QString &propertyName, const QVariant &propertyValue); /* 设置范围单元格的字体的任意属性 */
    void setRangeFontBold(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b);              /* 设置范围单元格字体是否加粗 */
    void setRangeFontUnderline(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b);     /* 设置范围单元格字体是否有下划线 */
    void setRangeFontSize(const int startRow, const int startColumn, const int endRow, const int endColumn, const int size);            /* 设置范围单元格字体尺寸 */
    void setRangeFontStrikethrough(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b); /* 设置范围单元格字体是否有中划线 */
    void setRangeFontSuperscript(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b);   /* 设置范围单元格字体是否是上标 */
    void setRangeFontSubscript(const int startRow, const int startColumn, const int endRow, const int endColumn, const bool b);     /* 设置范围单元格字体是否是下标 */

    //  字体对象,
    // .Name = "宋体"
    // .FontStyle = "加粗倾斜"
    // .Size = 12
    // .Strikethrough = True
    // .Superscript = False
    // .Subscript = False
    // .OutlineFont = False
    // .Shadow = False
    // .Underline = xlUnderlineStyleNone
    // .ThemeColor = xlThemeColorLight1
    // .TintAndShade = 0
    // .ThemeFont = xlThemeFontMajor
    //void setRangeNumberFormatLocal(const int startRow, const int startColumn, const int endRow, const int endColumn, const QString &numberFormatLocal);

    // 行对象,包含某一行或者多行的所有单元格
    QAxObject *getRows(const QString &name);                                                         /* 获取行对象 */
    QAxObject *getRows(const int startRow, const int endRow);                                   /* 获取行对象 */
    void setRowsProperty(const int startRow, const int endRow, const QString &propertyName, const QVariant &propertyValue);
    void setRowsHeight(const int startRow, const int endRow, const float height);        /* 设置行高 */
    void setRowsHAlignment(const int startRow, const int endRow, HAlignment align); /* 设置行水平对齐方式 */
    void setRowsVAlignment(const int startRow, const int endRow, VAlignment align); /* 设置行垂直对齐方式 */
    void setRowsMergeCells(const int startRow, const int endRow, bool b);
    void setRowsWrapText(const int startRow, const int endRow, bool b);

    // 列对象,包含某一列或者多列的所有单元格
    QAxObject *getColumns(const QString &name);                                                             /* 获取列对象 */
    QAxObject *getColumns(const int startColumn, const int endColumn);                              /* 获取列对象 */
    void setColumnsProperty(const int startColumn, const int endColumn, const QString &propertyName, const QVariant &propertyValue); /* 根据列的属性名设置属性值 */
    void setColumnsWidth(const int startColumn, const int endColumn, const float width);    /* 设置列宽 */
    void setColumnsHAlignment(const int startColumn, const int endColumn, HAlignment align); /* 设置列水平对齐方式 */
    void setColumnsVAlignment(const int startColumn, const int endColumn, VAlignment align); /* 设置列垂直对齐方式 */
    void setColumnsMergeCells(const int startColumn, const int endColumn, bool b);
    void setColumnsWrapText(const int startColumn, const int endColumn, bool b);

    // 单元格对象
    QAxObject *getCell(const int row, const int column);
    void setCellProperty(const int row, const int column, const QString &propertyName, const QVariant &propertyValue);
    void setCellText(const int row, const int column, const QString &text);

protected:
    bool initCOM();                             /* 初始化windows COM组件 */
    void deleteAxObjects();

private:
    QAxObject *mExcelApp;               /* excel应用程序实例 */
    QAxObject *mWorkBooks;              /* 所有的工作簿,excel应用一启动,便会获得所有工作簿 */
    QAxObject *mActiveWorkBook;     /* 活动工作簿,必须打开文件或者新建工作簿后,才会获得活动工作簿 */
    QAxObject *mActiveWorkSheet;   /* 活动工作表,必须获得活动工作簿后,才能获得活动的工作表 */

    bool            mIsValid;                   /* 如果某些原因导致对象初始化失败,比如计算机上的Excel软件损坏了等,那么这个对象是无效的 */
    QString     mErrorString;               /* excel对象的错误描述 */

    bool            mIsVisible;                 /* 打开的Excel应用程序是否可见 */
    bool            mIsExecuted;            /* excel应用是否已经运行 */
};

#endif // SEXCEL_H
