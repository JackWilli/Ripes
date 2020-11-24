#pragma once

#include <QByteArray>
#include <QStringList>

#include <map>
#include <set>
#include <variant>

#include "assemblererror.h"

namespace Ripes {
namespace AssemblerTmp {

using LineTokens = QStringList;
using Symbol = QString;
using Symbols = std::set<Symbol>;
using Directives = std::set<QString>;
using DirectivesLinePair = std::pair<Directives, LineTokens>;
using SymbolMap = std::map<Symbol, uint32_t>;
using ReverseSymbolMap = std::map<uint32_t, Symbol>;
using HandleDirectiveRes = std::variant<Error, std::optional<QByteArray>>;
struct TokenizedSrcLine {
    Symbols symbols;
    LineTokens tokens;
    Directives directives;
    unsigned sourceLine = 0;
    uint32_t programAddress = -1;
};
using SymbolLinePair = std::pair<Symbols, LineTokens>;
using SourceProgram = std::vector<TokenizedSrcLine>;
using NoPassResult = std::monostate;

enum class Segment { bss, data, text };
const static std::map<Segment, QString> s_segmentName = {{Segment::bss, ".bss"},
                                                         {Segment::data, ".data"},
                                                         {Segment::text, ".text"}};
struct Program {
    std::map<Segment, QByteArray> segments;
};

/**
 * @brief The Result struct
 * An assembly result is determined to be valid iff errors is empty.
 */
struct AssembleResult {
    Errors errors;
    Program program;
};

struct DisassembleResult {
    Errors errors;
    QStringList program;
};

}  // namespace AssemblerTmp

}  // namespace Ripes
