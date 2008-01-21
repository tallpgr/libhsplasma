#include "pfPrcHelper.h"

pfPrcHelper::pfPrcHelper(hsStream* S)
           : iLvl(0), inTag(false), file(S), excludes(0) {
    startPrc();
}

pfPrcHelper::~pfPrcHelper() {
    finalize();
}

hsStream* pfPrcHelper::getStream() { return file; }

void pfPrcHelper::exclude(PrcExclude excl) {
    excludes |= excl;
}

bool pfPrcHelper::isExcluded(PrcExclude excl) {
    return (excludes & excl) != 0;
}

void pfPrcHelper::writeTabbed(const char* str) {
    for (int i=0; i<iLvl; i++) file->writeStr("\t");
    file->writeStr(str);
}

void pfPrcHelper::startTag(const char* name) {
    if (inTag) endTag();
    char buf[256];
    snprintf(buf, 256, "<%s", name);
    writeTabbed(buf);
    openTags.push(name);
    inTag = true;
}

void pfPrcHelper::writeParam(const char* name, const char* value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%s\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const int value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%d\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const unsigned int value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%u\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const float value) {
    writeParam(name, (double)value);
}

void pfPrcHelper::writeParam(const char* name, const double value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%g\"", name, value);
    file->writeStr(buf);
}

void pfPrcHelper::writeParam(const char* name, const bool value) {
    char buf[256];
    snprintf(buf, 256, " %s=\"%s\"", name, value ? "True" : "False");
    file->writeStr(buf);
}

void pfPrcHelper::endTag(bool isShort) {
    char buf[6];
    snprintf(buf, 6, "%s>\n", isShort ? " /" : "");
    file->writeStr(buf);
    if (!isShort)
        iLvl++;
    else
        openTags.pop();
    inTag = false;
}

void pfPrcHelper::endTagNoBreak() {
    file->writeStr(">");
    iLvl++;
    inTag = false;
}

void pfPrcHelper::writeSimpleTag(const char* name, bool isShort) {
    startTag(name);
    endTag(isShort);
}

void pfPrcHelper::writeTagNoBreak(const char* name) {
    startTag(name);
    endTagNoBreak();
}

void pfPrcHelper::closeTag() {
    char buf[256];
    iLvl--;
    snprintf(buf, 256, "</%s>\n", openTags.pop());
    writeTabbed(buf);
}

void pfPrcHelper::closeTagNoBreak() {
    char buf[256];
    iLvl--;
    snprintf(buf, 256, "</%s>\n", openTags.pop());
    file->writeStr(buf);
}

void pfPrcHelper::writeComment(const char* comment) {
    writeTabbed("<!-- ");
    file->writeStr(comment);
    file->writeStr(" -->\n");
}

void pfPrcHelper::startPrc() {
    file->writeStr("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n");
}

void pfPrcHelper::finalize() {
    if (inTag) endTag();
    while (!openTags.empty()) closeTag();
}
