#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Line
{
    std::vector<string> words;
    size_t width;
};

vector<string> fullJustify(vector<string>& words, int maxWidth) {
    std::vector<Line> lines{};
    size_t len = 0;
    vector<string> line{};
    // 将单词按长度分行
    for(auto& word : words){
        // 还需要保留空格
        if (len += word.size(); (len + line.size()) > maxWidth) {
            lines.emplace_back(std::move(line), len - word.size());
            line.clear();
            len = word.size();
        }
        line.push_back(std::move(word));
    }
    if(!line.empty()){
        lines.emplace_back(std::move(line), len);
    }

    std::vector<string> ret{};
    ret.reserve(lines.size());
    // 处理所有的行
    for(auto it = std::begin(lines); it != std::end(lines); std::advance(it, 1)){
        auto& [words, width] = *it;
        size_t spaceCount = maxWidth - width;
        string line{};

        // 最后一行
        if(it == std::prev(std::end(lines)) || (words.size() - 1 == 0)){
            size_t numSpcae = spaceCount;
            for(auto& word : words){
                line += word;
                if(numSpcae != 0){
                    line += " ";
                    numSpcae--;
                }
            }
            for(size_t i = 0; i < numSpcae; line += " ", ++i);
        }
        else{
            // 每个间隔的空格数
            size_t numPreWorld = spaceCount / (words.size() - 1);
            size_t numExtraSpace = spaceCount % (words.size() - 1);
            line += words.front();
            // 将行内的单词对其
            for(size_t i = 1; i < words.size(); ++i){
                string space{};
                if(numExtraSpace != 0){
                    space += " ";
                    numExtraSpace--;
                }
                for(size_t j = 0; j < numPreWorld; space += " ", ++j);

                line += space + words[i];
            }
        }
        ret.push_back(std::move(line));
    }
    return ret;
}

int main()
{
    vector<string> words{"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
    auto lines = fullJustify(words, 20);
    for(const auto& line : lines){
        assert(line.size() == 20);
    }
    return 0;
}