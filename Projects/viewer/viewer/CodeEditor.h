
#ifndef CODE_EDITOR_H
#define CODE_EDITOR_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtGui/QSyntaxHighlighter>
#include <QtWidgets/QAbstractScrollArea>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>

class LineNumberArea;
class CodeEditor;
class Highlighter;

class CodeEditor : public QPlainTextEdit
{
	Q_OBJECT

		/*----------Variables declaration----------*/
private:
	LineNumberArea * lineNumberArea;
	QList<QTextEdit::ExtraSelection> extraSelections;
	qint32 numOfErrors/* = 0*/;

public:
	Highlighter * highlighter;
	bool isConsoleWidget;
	QString fileName;

	/*----------Functions declaration----------*/
public:
	CodeEditor(bool isConsole = 0, QWidget* parent = 0);
	~CodeEditor();

public:
	void			lineNumberAreaPaintEvent(QPaintEvent* ev);
	qint32			lineNumberAreaWidth();
	void			clearExtraSelections();
	void			loadFile(QString fileName);
	void			reloadFile();
	void			save();
	QString			saveAs();
	void			findText(QString str, int isBackward);

private:
	void resizeEvent(QResizeEvent* ev) Q_DECL_OVERRIDE;

	/*----------Slots declaration----------*/
	private slots:
	void			slotUpdateLineNumberAreaWidth(qint32 newBlockCount);
	void			slotHighlightCurrentLine();
	void			slotUpdateLineNumberArea(const QRect &, qint32);
	void			slotOnTextChanged();
};

class LineNumberArea : public QWidget
{
	Q_OBJECT

private:
	CodeEditor * codeEditor;

public:
	LineNumberArea(CodeEditor* editor) : QWidget(editor) {
		codeEditor = editor;
	}
	QSize sizeHint() const Q_DECL_OVERRIDE {
		return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent* ev) Q_DECL_OVERRIDE {
		codeEditor->lineNumberAreaPaintEvent(ev);
	}

};

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT
public:
	int multilineCommentsEnabled/* = 0*/;
public:
	Highlighter(QTextDocument* parent = 0) : QSyntaxHighlighter(parent) {}

public:
	void addHighlightningRule(QRegExp pattern, QTextCharFormat format) {
		HighlightningRule rule;
		rule.pattern = pattern;
		rule.format = format;
		rules.push_back(rule);
	}

public:
	void highlightBlock(const QString &text) Q_DECL_OVERRIDE {
		/*Highlight line*/
		foreach(const HighlightningRule &rule, rules) {
			QRegExp expression(rule.pattern);
			qint32 index = expression.indexIn(text);
			while (index >= 0) {
				qint32 length = expression.matchedLength();
				setFormat(index, length, rule.format);
				index = expression.indexIn(text, index + length);
			}
		}

		/*Highlight multiline comments*/
		if (multilineCommentsEnabled) {
			setCurrentBlockState(0);
			int startIndex = 0;
			if (previousBlockState() != 1)
				startIndex = commentStartExpression.indexIn(text);
			while (startIndex >= 0) {
				int endIndex = commentEndExpression.indexIn(text, startIndex);
				int commentLength;
				if (endIndex == -1) {
					setCurrentBlockState(1);
					commentLength = text.length() - startIndex;
				}
				else {
					commentLength = endIndex - startIndex
						+ commentEndExpression.matchedLength();
				}
				setFormat(startIndex, commentLength, multiLineCommentFormat);
				startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
			}
		}
	}

public:
	struct HighlightningRule {
		QRegExp pattern;
		QTextCharFormat format;
	};

	QVector<HighlightningRule> rules;

	QRegExp commentStartExpression;
	QRegExp commentEndExpression;

	QTextCharFormat multiLineCommentFormat;

};


#endif //CODE_EDITOR_H
