#pragma once
#include "flags.h"
#include <cstdint>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>
namespace icon {

/// 储存图标的信息
class IconInfo {
private:
  std::string icon; //< Nerd font 中使用的图标
  uint8_t color[3]; //< 图标颜色rgb信息
  bool executable;  //< 是否可执行
public:
  static std::string getColor(int r, int g, int b) {
    return std::string("\033[38;2;") + std::to_string(r) + ";" +
           std::to_string(g) + ";" + std::to_string(b) + "m";
    /* const std::string format("\033[38;2;%03d;%03d;%03dm"); */
    /* char buf[30]; */
    /* sprintf(buf, format.c_str(), r, g, b); */
    /* return buf; */
  }
  IconInfo() = default;
  IconInfo(const std::string &ic, std::vector<uint8_t> co)
      : icon(ic), color{co[0], co[1], co[2]}, executable(false) {}
  std::string getGraph() const { return icon; } //< 获取图标
  std::string getColor() const {
    auto flag = core::Flags::getInstance().getFlag();
    if (flag & core::Flags::flag_c) {
      return "\033[38;2;255;255;255m";
    }
    if (executable) {
      return "\033[38;2;76;175;080m";
    } else {
      return IconInfo::getColor(color[0], color[1], color[2]);
    }
  };                                  //< 获取颜色
  void toExe() { executable = true; } //< 标记为可执行文件
};
} // namespace icon

namespace icon {
/// 通用图标设置
const std::unordered_map<std::string, IconInfo> iconSet = {
    {"html", {"\uf13b", {228, 79, 57}}},             // html
    {"markdown", {"\uf853", {66, 165, 245}}},        // markdown
    {"css", {"\uf81b", {66, 165, 245}}},             // css
    {"css-map", {"\ue749", {66, 165, 245}}},         // css-map
    {"sass", {"\ue603", {237, 80, 122}}},            // sass
    {"less", {"\ue60b", {2, 119, 189}}},             // less
    {"json", {"\ue60b", {251, 193, 60}}},            // json
    {"yaml", {"\ue60b", {244, 68, 62}}},             // yaml
    {"xml", {"\uf72d", {64, 153, 69}}},              // xml
    {"image", {"\uf71e", {48, 166, 154}}},           // image
    {"javascript", {"\ue74e", {255, 202, 61}}},      // javascript
    {"javascript-map", {"\ue781", {255, 202, 61}}},  // javascript-map
    {"test-jsx", {"\uf595", {35, 188, 212}}},        // test-jsx
    {"test-js", {"\uf595", {255, 202, 61}}},         // test-js
    {"react", {"\ue7ba", {35, 188, 212}}},           // react
    {"react_ts", {"\ue7ba", {36, 142, 211}}},        // react_ts
    {"settings", {"\uf013", {66, 165, 245}}},        // settings
    {"typescript", {"\ue628", {3, 136, 209}}},       // typescript
    {"typescript-def", {"\ufbe4", {3, 136, 209}}},   // typescript-def
    {"test-ts", {"\uf595", {3, 136, 209}}},          // test-ts
    {"pdf", {"\uf724", {244, 68, 62}}},              // pdf
    {"table", {"\uf71a", {139, 195, 74}}},           // table
    {"visualstudio", {"\ue70c", {173, 99, 188}}},    // visualstudio
    {"database", {"\ue706", {255, 202, 61}}},        // database
    {"mysql", {"\ue704", {1, 94, 134}}},             // mysql
    {"postgresql", {"\ue76e", {49, 99, 140}}},       // postgresql
    {"sqlite", {"\ue7c4", {1, 57, 84}}},             // sqlite
    {"csharp", {"\uf81a", {2, 119, 189}}},           // csharp
    {"zip", {"\uf410", {175, 180, 43}}},             // zip
    {"exe", {"\uf2d0", {229, 77, 58}}},              // exe
    {"java", {"\uf675", {244, 68, 62}}},             // java
    {"c", {"\ufb70", {2, 119, 189}}},                // c
    {"cpp", {"\ufb71", {2, 119, 189}}},              // cpp
    {"go", {"\ufcd1", {32, 173, 194}}},              // go
    {"go-mod", {"\ufcd1", {237, 80, 122}}},          // go-mod
    {"go-test", {"\ufcd1", {255, 213, 79}}},         // go-test
    {"python", {"\uf81f", {52, 102, 143}}},          // python
    {"python-misc", {"\uf820", {130, 61, 28}}},      // python-misc
    {"url", {"\uf836", {66, 165, 245}}},             // url
    {"console", {"\uf68c", {250, 111, 66}}},         // console
    {"word", {"\uf72b", {1, 87, 155}}},              // word
    {"certificate", {"\uf623", {249, 89, 63}}},      // certificate
    {"key", {"\uf805", {48, 166, 154}}},             // key
    {"font", {"\uf031", {244, 68, 62}}},             // font
    {"lib", {"\uf831", {139, 195, 74}}},             // lib
    {"ruby", {"\ue739", {229, 61, 58}}},             // ruby
    {"gemfile", {"\ue21e", {229, 61, 58}}},          // gemfile
    {"fsharp", {"\ue7a7", {55, 139, 186}}},          // fsharp
    {"swift", {"\ufbe3", {249, 95, 63}}},            // swift
    {"docker", {"\uf308", {1, 135, 201}}},           // docker
    {"powerpoint", {"\uf726", {209, 71, 51}}},       // powerpoint
    {"video", {"\uf72a", {253, 154, 62}}},           // video
    {"virtual", {"\uf822", {3, 155, 229}}},          // virtual
    {"email", {"\uf6ed", {66, 165, 245}}},           // email
    {"audio", {"\ufb75", {239, 83, 80}}},            // audio
    {"coffee", {"\uf675", {66, 165, 245}}},          // coffee
    {"document", {"\uf718", {66, 165, 245}}},        // document
    {"rust", {"\ue7a8", {250, 111, 66}}},            // rust
    {"raml", {"\ue60b", {66, 165, 245}}},            // raml
    {"xaml", {"\ufb72", {66, 165, 245}}},            // xaml
    {"haskell", {"\ue61f", {254, 168, 62}}},         // haskell
    {"git", {"\ue702", {229, 77, 58}}},              // git
    {"lua", {"\ue620", {66, 165, 245}}},             // lua
    {"clojure", {"\ue76a", {100, 221, 23}}},         // clojure
    {"groovy", {"\uf2a6", {41, 198, 218}}},          // groovy
    {"r", {"\ufcd2", {25, 118, 210}}},               // r
    {"dart", {"\ue798", {87, 182, 240}}},            // dart
    {"mxml", {"\uf72d", {254, 168, 62}}},            // mxml
    {"assembly", {"\uf471", {250, 109, 63}}},        // assembly
    {"vue", {"\ufd42", {65, 184, 131}}},             // vue
    {"vue-config", {"\ufd42", {58, 121, 110}}},      // vue-config
    {"lock", {"\uf83d", {255, 213, 79}}},            // lock
    {"handlebars", {"\ue60f", {250, 111, 66}}},      // handlebars
    {"perl", {"\ue769", {149, 117, 205}}},           // perl
    {"elixir", {"\ue62d", {149, 117, 205}}},         // elixir
    {"erlang", {"\ue7b1", {244, 68, 62}}},           // erlang
    {"twig", {"\ue61c", {155, 185, 47}}},            // twig
    {"julia", {"\ue624", {134, 82, 159}}},           // julia
    {"elm", {"\ue62c", {96, 181, 204}}},             // elm
    {"smarty", {"\uf834", {255, 207, 60}}},          // smarty
    {"stylus", {"\ue600", {192, 202, 51}}},          // stylus
    {"verilog", {"\ufb19", {250, 111, 66}}},         // verilog
    {"robot", {"\ufba7", {249, 89, 63}}},            // robot
    {"solidity", {"\ufcb9", {3, 136, 209}}},         // solidity
    {"yang", {"\ufb7e", {66, 165, 245}}},            // yang
    {"vercel", {"\uf47e", {207, 216, 220}}},         // vercel
    {"applescript", {"\uf302", {120, 144, 156}}},    // applescript
    {"cake", {"\uf5ea", {250, 111, 66}}},            // cake
    {"nim", {"\uf6a4", {255, 202, 61}}},             // nim
    {"todo", {"\uf058", {124, 179, 66}}},            // todo
    {"nix", {"\uf313", {80, 117, 193}}},             // nix
    {"http", {"\uf484", {66, 165, 245}}},            // http
    {"webpack", {"\ufc29", {142, 214, 251}}},        // webpack
    {"ionic", {"\ue7a9", {79, 143, 247}}},           // ionic
    {"gulp", {"\ue763", {229, 61, 58}}},             // gulp
    {"nodejs", {"\uf898", {139, 195, 74}}},          // nodejs
    {"npm", {"\ue71e", {203, 56, 55}}},              // npm
    {"yarn", {"\uf61a", {44, 142, 187}}},            // yarn
    {"android", {"\uf531", {139, 195, 74}}},         // android
    {"tune", {"\ufb69", {251, 193, 60}}},            // tune
    {"contributing", {"\uf64d", {255, 202, 61}}},    // contributing
    {"readme", {"\uf7fb", {66, 165, 245}}},          // readme
    {"changelog", {"\ufba6", {139, 195, 74}}},       // changelog
    {"credits", {"\uf75f", {156, 204, 101}}},        // credits
    {"authors", {"\uf0c0", {244, 68, 62}}},          // authors
    {"favicon", {"\ue623", {255, 213, 79}}},         // favicon
    {"karma", {"\ue622", {60, 190, 174}}},           // karma
    {"travis", {"\ue77e", {203, 58, 73}}},           // travis
    {"heroku", {"\ue607", {105, 99, 185}}},          // heroku
    {"gitlab", {"\uf296", {226, 69, 57}}},           // gitlab
    {"bower", {"\ue61a", {239, 88, 60}}},            // bower
    {"conduct", {"\uf64b", {205, 220, 57}}},         // conduct
    {"jenkins", {"\ue767", {240, 214, 183}}},        // jenkins
    {"code-climate", {"\uf7f4", {238, 238, 238}}},   // code-climate
    {"log", {"\uf719", {175, 180, 43}}},             // log
    {"ejs", {"\ue618", {255, 202, 61}}},             // ejs
    {"grunt", {"\ue611", {251, 170, 61}}},           // grunt
    {"django", {"\ue71d", {67, 160, 71}}},           // django
    {"makefile", {"\uf728", {239, 83, 80}}},         // makefile
    {"bitbucket", {"\uf171", {31, 136, 229}}},       // bitbucket
    {"d", {"\ue7af", {244, 68, 62}}},                // d
    {"mdx", {"\uf853", {255, 202, 61}}},             // mdx
    {"azure-pipelines", {"\uf427", {20, 101, 192}}}, // azure-pipelines
    {"azure", {"\ufd03", {31, 136, 229}}},           // azure
    {"razor", {"\uf564", {66, 165, 245}}},           // razor
    {"asciidoc", {"\uf718", {244, 68, 62}}},         // asciidoc
    {"edge", {"\uf564", {239, 111, 60}}},            // edge
    {"scheme", {"\ufb26", {244, 68, 62}}},           // scheme
    {"3d", {"\ue79b", {40, 182, 246}}},              // 3d
    {"svg", {"\ufc1f", {255, 181, 62}}},             // svg
    {"vim", {"\ue62b", {67, 160, 71}}},              // vim
    {"moonscript", {"\uf186", {251, 193, 60}}},      // moonscript
    {"codeowners", {"\uf507", {175, 180, 43}}},      // codeowners
    {"disc", {"\ue271", {176, 190, 197}}},           // disc
    {"fortran", {"F", {250, 111, 66}}},              // fortran
    {"tcl", {"\ufbd1", {239, 83, 80}}},              // tcl
    {"liquid", {"\ue275", {40, 182, 246}}},          // liquid
    {"prolog", {"\ue7a1", {239, 83, 80}}},           // prolog
    {"husky", {"\uf8e8", {229, 229, 229}}},          // husky
    {"coconut", {"\uf5d2", {141, 110, 99}}},         // coconut
    {"sketch", {"\uf6c7", {255, 194, 61}}},          // sketch
    {"pawn", {"\ue261", {239, 111, 60}}},            // pawn
    {"commitlint", {"\ufc16", {43, 150, 137}}},      // commitlint
    {"dhall", {"\uf448", {120, 144, 156}}},          // dhall
    {"dune", {"\uf7f4", {244, 127, 61}}},            // dune
    {"shaderlab", {"\ufbad", {25, 118, 210}}},       // shaderlab
    {"command", {"\ufb32", {175, 188, 194}}},        // command
    {"stryker", {"\uf05b", {239, 83, 80}}},          // stryker
    {"modernizr", {"\ue720", {234, 72, 99}}},        // modernizr
    {"roadmap", {"\ufb6d", {48, 166, 154}}},         // roadmap
    {"debian", {"\uf306", {211, 61, 76}}},           // debian
    {"ubuntu", {"\uf31c", {214, 73, 53}}},           // ubuntu
    {"arch", {"\uf303", {33, 142, 202}}},            // arch
    {"redhat", {"\uf316", {231, 61, 58}}},           // redhat
    {"gentoo", {"\uf30d", {148, 141, 211}}},         // gentoo
    {"linux", {"\ue712", {238, 207, 55}}},           // linux
    {"raspberry-pi", {"\uf315", {208, 60, 76}}},     // raspberry-pi
    {"manjaro", {"\uf312", {73, 185, 90}}},          // manjaro
    {"opensuse", {"\uf314", {111, 180, 36}}},        // opensuse
    {"fedora", {"\uf30a", {52, 103, 172}}},          // fedora
    {"freebsd", {"\uf30c", {175, 44, 42}}},          // freebsd
    {"centOS", {"\uf304", {157, 83, 135}}},          // centOS
    {"alpine", {"\uf300", {14, 87, 123}}},           // alpine
    {"mint", {"\uf30f", {125, 190, 58}}},            // mint
    {"routing", {"\ufb40", {67, 160, 71}}},          // routing
    {"laravel", {"\ue73f", {248, 80, 81}}},          // laravel
    {"pug", {"\ue60e", {239, 204, 163}}}, // pug (Not supported by nerdFont)
    {"blink",
     {"\uf72a",
      {249, 169, 60}}}, // blink (The Foundry Nuke) (Not supported by nerdFont)
    {"postcss",
     {"\uf81b", {244, 68, 62}}},          // postcss (Not supported by nerdFont)
    {"jinja", {"\ue000", {174, 44, 42}}}, // jinja (Not supported by nerdFont)
    {"sublime",
     {"\ue7aa", {239, 148, 58}}}, // sublime (Not supported by nerdFont)
    {"markojs",
     {"\uf13b", {2, 119, 189}}}, // markojs (Not supported by nerdFont)
    {"vscode",
     {"\ue70c", {33, 150, 243}}}, // vscode (Not supported by nerdFont)
    {"qsharp",
     {"\uf292", {251, 193, 60}}},          // qsharp (Not supported by nerdFont)
    {"vala", {"\uf7ab", {149, 117, 205}}}, // vala (Not supported by nerdFont)
    {"zig", {"Z", {249, 169, 60}}},        // zig (Not supported by nerdFont)
    {"h", {"h", {2, 119, 189}}},           // h (Not supported by nerdFont)
    {"hpp", {"h", {2, 119, 189}}},         // hpp (Not supported by nerdFont)
    {"powershell",
     {"\ufcb5", {5, 169, 244}}}, // powershell (Not supported by nerdFont)
    {"gradle",
     {"\ufcc4", {29, 151, 167}}}, // gradle (Not supported by nerdFont)
    {"arduino",
     {"\ue255", {35, 151, 156}}},        // arduino (Not supported by nerdFont)
    {"tex", {"\uf783", {66, 165, 245}}}, // tex (Not supported by nerdFont)
    {"graphql",
     {"\ue284", {237, 80, 122}}}, // graphql (Not supported by nerdFont)
    {"kotlin",
     {"\ue70e", {139, 195, 74}}}, // kotlin (Not supported by nerdFont)
    {"actionscript",
     {"\ufb25", {244, 68, 62}}}, // actionscript (Not supported by nerdFont)
    {"autohotkey",
     {"\uf812", {76, 175, 80}}}, // autohotkey (Not supported by nerdFont)
    {"flash", {"\uf740", {198, 52, 54}}},   // flash (Not supported by nerdFont)
    {"swc", {"\ufbd3", {198, 52, 54}}},     // swc (Not supported by nerdFont)
    {"cmake", {"\uf425", {178, 178, 179}}}, // cmake (Not supported by nerdFont)
    {"nuxt", {"\ue2a6", {65, 184, 131}}},   // nuxt (Not supported by nerdFont)
    {"ocaml", {"\uf1ce", {253, 154, 62}}},  // ocaml (Not supported by nerdFont)
    {"haxe", {"\uf425", {246, 137, 61}}},   // haxe (Not supported by nerdFont)
    {"puppet",
     {"\uf595", {251, 193, 60}}}, // puppet (Not supported by nerdFont)
    {"purescript",
     {"\uf670", {66, 165, 245}}}, // purescript (Not supported by nerdFont)
    {"merlin",
     {"\uf136", {66, 165, 245}}},        // merlin (Not supported by nerdFont)
    {"mjml", {"\ue714", {249, 89, 63}}}, // mjml (Not supported by nerdFont)
    {"terraform",
     {"\ue20f", {92, 107, 192}}}, // terraform (Not supported by nerdFont)
    {"apiblueprint",
     {"\uf031", {66, 165, 245}}}, // apiblueprint (Not supported by nerdFont)
    {"slim", {"\uf24e", {245, 129, 61}}},  // slim (Not supported by nerdFont)
    {"babel", {"\uf5a0", {253, 217, 59}}}, // babel (Not supported by nerdFont)
    {"codecov",
     {"\ue37c", {237, 80, 122}}}, // codecov (Not supported by nerdFont)
    {"protractor",
     {"\uf288", {229, 61, 58}}}, // protractor (Not supported by nerdFont)
    {"eslint",
     {"\ufbf6", {121, 134, 203}}}, // eslint (Not supported by nerdFont)
    {"mocha", {"\uf6a9", {161, 136, 127}}}, // mocha (Not supported by nerdFont)
    {"firebase",
     {"\ue787", {251, 193, 60}}}, // firebase (Not supported by nerdFont)
    {"stylelint",
     {"\ufb76", {207, 216, 220}}}, // stylelint (Not supported by nerdFont)
    {"prettier",
     {"\uf8e2", {86, 179, 180}}},   // prettier (Not supported by nerdFont)
    {"jest", {"J", {244, 85, 62}}}, // jest (Not supported by nerdFont)
    {"storybook",
     {"\ufd2c", {237, 80, 122}}}, // storybook (Not supported by nerdFont)
    {"fastlane",
     {"\ufbff", {149, 119, 232}}}, // fastlane (Not supported by nerdFont)
    {"helm", {"\ufd31", {32, 173, 194}}},  // helm (Not supported by nerdFont)
    {"i18n", {"\uf7be", {121, 134, 203}}}, // i18n (Not supported by nerdFont)
    {"semantic-release",
     {"\uf70f",
      {245, 245, 245}}}, // semantic-release (Not supported by nerdFont)
    {"godot", {"\ufba7", {79, 195, 247}}}, // godot (Not supported by nerdFont)
    {"godot-assets",
     {"\ufba7", {129, 199, 132}}}, // godot-assets (Not supported by nerdFont)
    {"vagrant",
     {"\uf27d", {20, 101, 192}}}, // vagrant (Not supported by nerdFont)
    {"tailwindcss",
     {"\ufc8b", {77, 182, 172}}}, // tailwindcss (Not supported by nerdFont)
    {"gcp", {"\uf662", {70, 136, 250}}},   // gcp (Not supported by nerdFont)
    {"opam", {"\uf1ce", {255, 213, 79}}},  // opam (Not supported by nerdFont)
    {"pascal", {"\uf8da", {3, 136, 209}}}, // pascal (Not supported by nerdFont)
    {"nuget", {"\ue77f", {3, 136, 209}}},  // nuget (Not supported by nerdFont)
    {"denizenscript",
     {"D", {255, 213, 79}}}, // denizenscript (Not supported by nerdFont)
    {"dir-config", {"\ue5fc", {32, 173, 194}}},       // dir-config
    {"dir-controller", {"\ue5fc", {255, 194, 61}}},   // dir-controller
    {"dir-git", {"\ue5fb", {250, 111, 66}}},          // dir-git
    {"dir-github", {"\ue5fd", {84, 110, 122}}},       // dir-github
    {"dir-npm", {"\ue5fa", {203, 56, 55}}},           // dir-npm
    {"dir-include", {"\uf756", {3, 155, 229}}},       // dir-include
    {"dir-import", {"\uf756", {175, 180, 43}}},       // dir-import
    {"dir-upload", {"\uf758", {250, 111, 66}}},       // dir-upload
    {"dir-download", {"\uf74c", {76, 175, 80}}},      // dir-download
    {"dir-secure", {"\uf74f", {249, 169, 60}}},       // dir-secure
    {"dir-images", {"\uf74e", {43, 150, 137}}},       // dir-images
    {"dir-environment", {"\uf74e", {102, 187, 106}}}, // dir-environment
    {"dir-source", {"\uf74a", {0, 255, 154}}},
    {"dir-test", {"\uf74a", {30, 144, 255}}},
};
} // namespace icon

namespace icon {
const std::unordered_map<std::string, IconInfo> iconInfo{
    {"dir", {"\uf74a", {224, 177, 77}}},
    {"diropen", {"\ufc6e", {224, 177, 77}}},
    {"hiddendir", {"\uf755", {224, 177, 77}}},
    {"exe", {"\uf713", {76, 175, 80}}},
    {"file", {"\uf723", {65, 129, 190}}},
    {"hiddenfile", {"\ufb12", {65, 129, 190}}},
};
}
