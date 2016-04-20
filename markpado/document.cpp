#include "document.h"

void Document::setText(const QString &text) {
    if (text == m_text)
        return;
    m_text = text;
    emit textChanged(m_text);
}