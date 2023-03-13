#pragma once
#include <string>
#include<unordered_map>
#include "icons.h"

namespace icon{
const  std::unordered_map<std::string, IconInfo> iconFilename{
  {".pug-lintrc",                         iconSet.at("pug")},
  {".pug-lintrc.js",                      iconSet.at("pug")},
  {".pug-lintrc.json",                    iconSet.at("pug")},
  {".jscsrc",                             iconSet.at("json")},
  {".jshintrc",                           iconSet.at("json")},
  {"composer.lock",                       iconSet.at("json")},
  {".jsbeautifyrc",                       iconSet.at("json")},
  {".esformatter",                        iconSet.at("json")},
  {"cdp.pid",                             iconSet.at("json")},
  {".mjmlconfig",                         iconSet.at("json")},
  {".htaccess",                           iconSet.at("xml")},
  {".jshintignore",                       iconSet.at("settings")},
  {".buildignore",                        iconSet.at("settings")},
  {".mrconfig",                           iconSet.at("settings")},
  {".yardopts",                           iconSet.at("settings")},
  {"manifest.mf",                         iconSet.at("settings")},
  {".clang-format",                       iconSet.at("settings")},
  {".clang-tidy",                         iconSet.at("settings")},
  {"go.mod",                              iconSet.at("go-mod")},
  {"go.sum",                              iconSet.at("go-mod")},
  {"requirements.txt",                    iconSet.at("python-misc")},
  {"pipfile",                             iconSet.at("python-misc")},
  {".python-version",                     iconSet.at("python-misc")},
  {"manifest.in",                         iconSet.at("python-misc")},
  {"gradle.properties",                   iconSet.at("gradle")},
  {"gradlew",                             iconSet.at("gradle")},
  {"gradle-wrapper.properties",           iconSet.at("gradle")},
  {"license",                             iconSet.at("certificate")},
  {"license.md",                          iconSet.at("certificate")},
  {"license.txt",                         iconSet.at("certificate")},
  {"licence",                             iconSet.at("certificate")},
  {"licence.md",                          iconSet.at("certificate")},
  {"licence.txt",                         iconSet.at("certificate")},
  {"unlicense",                           iconSet.at("certificate")},
  {"unlicense.md",                        iconSet.at("certificate")},
  {"unlicense.txt",                       iconSet.at("certificate")},
  {".htpasswd",                           iconSet.at("key")},
  {"gemfile",                             iconSet.at("gemfile")},
  {"dockerfile",                          iconSet.at("docker")},
  {"dockerfile.prod",                     iconSet.at("docker")},
  {"dockerfile.production",               iconSet.at("docker")},
  {"docker-compose.yml",                  iconSet.at("docker")},
  {"docker-compose.yaml",                 iconSet.at("docker")},
  {"docker-compose.dev.yml",              iconSet.at("docker")},
  {"docker-compose.local.yml",            iconSet.at("docker")},
  {"docker-compose.ci.yml",               iconSet.at("docker")},
  {"docker-compose.override.yml",         iconSet.at("docker")},
  {"docker-compose.staging.yml",          iconSet.at("docker")},
  {"docker-compose.prod.yml",             iconSet.at("docker")},
  {"docker-compose.production.yml",       iconSet.at("docker")},
  {"docker-compose.test.yml",             iconSet.at("docker")},
  {".mailmap",                            iconSet.at("email")},
  {".graphqlconfig",                      iconSet.at("graphql")},
  {".gitignore",                          iconSet.at("git")},
  {".gitconfig",                          iconSet.at("git")},
  {".gitattributes",                      iconSet.at("git")},
  {".gitmodules",                         iconSet.at("git")},
  {".gitkeep",                            iconSet.at("git")},
  {"git-history",                         iconSet.at("git")},
  {".luacheckrc",                         iconSet.at("lua")},
  {".Rhistory",                           iconSet.at("r")},
  {"cmakelists.txt",                      iconSet.at("cmake")},
  {"cmakecache.txt",                      iconSet.at("cmake")},
  {"vue.config.js",                       iconSet.at("vue-config")},
  {"vue.config.ts",                       iconSet.at("vue-config")},
  {"nuxt.config.js",                      iconSet.at("nuxt")},
  {"nuxt.config.ts",                      iconSet.at("nuxt")},
  {"security.md",                         iconSet.at("lock")},
  {"security.txt",                        iconSet.at("lock")},
  {"security",                            iconSet.at("lock")},
  {"vercel.json",                         iconSet.at("vercel")},
  {".vercelignore",                       iconSet.at("vercel")},
  {"now.json",                            iconSet.at("vercel")},
  {".nowignore",                          iconSet.at("vercel")},
  {"postcss.config.js",                   iconSet.at("postcss")},
  {".postcssrc.js",                       iconSet.at("postcss")},
  {".postcssrc",                          iconSet.at("postcss")},
  {".postcssrc.json",                     iconSet.at("postcss")},
  {".postcssrc.yml",                      iconSet.at("postcss")},
  {"CNAME",                               iconSet.at("http")},
  {"webpack.js",                          iconSet.at("webpack")},
  {"webpack.ts",                          iconSet.at("webpack")},
  {"webpack.base.js",                     iconSet.at("webpack")},
  {"webpack.base.ts",                     iconSet.at("webpack")},
  {"webpack.config.js",                   iconSet.at("webpack")},
  {"webpack.config.ts",                   iconSet.at("webpack")},
  {"webpack.common.js",                   iconSet.at("webpack")},
  {"webpack.common.ts",                   iconSet.at("webpack")},
  {"webpack.config.common.js",            iconSet.at("webpack")},
  {"webpack.config.common.ts",            iconSet.at("webpack")},
  {"webpack.config.common.babel.js",      iconSet.at("webpack")},
  {"webpack.config.common.babel.ts",      iconSet.at("webpack")},
  {"webpack.dev.js",                      iconSet.at("webpack")},
  {"webpack.dev.ts",                      iconSet.at("webpack")},
  {"webpack.development.js",              iconSet.at("webpack")},
  {"webpack.development.ts",              iconSet.at("webpack")},
  {"webpack.config.dev.js",               iconSet.at("webpack")},
  {"webpack.config.dev.ts",               iconSet.at("webpack")},
  {"webpack.config.dev.babel.js",         iconSet.at("webpack")},
  {"webpack.config.dev.babel.ts",         iconSet.at("webpack")},
  {"webpack.prod.js",                     iconSet.at("webpack")},
  {"webpack.prod.ts",                     iconSet.at("webpack")},
  {"webpack.production.js",               iconSet.at("webpack")},
  {"webpack.production.ts",               iconSet.at("webpack")},
  {"webpack.server.js",                   iconSet.at("webpack")},
  {"webpack.server.ts",                   iconSet.at("webpack")},
  {"webpack.client.js",                   iconSet.at("webpack")},
  {"webpack.client.ts",                   iconSet.at("webpack")},
  {"webpack.config.server.js",            iconSet.at("webpack")},
  {"webpack.config.server.ts",            iconSet.at("webpack")},
  {"webpack.config.client.js",            iconSet.at("webpack")},
  {"webpack.config.client.ts",            iconSet.at("webpack")},
  {"webpack.config.production.babel.js",  iconSet.at("webpack")},
  {"webpack.config.production.babel.ts",  iconSet.at("webpack")},
  {"webpack.config.prod.babel.js",        iconSet.at("webpack")},
  {"webpack.config.prod.babel.ts",        iconSet.at("webpack")},
  {"webpack.config.prod.js",              iconSet.at("webpack")},
  {"webpack.config.prod.ts",              iconSet.at("webpack")},
  {"webpack.config.production.js",        iconSet.at("webpack")},
  {"webpack.config.production.ts",        iconSet.at("webpack")},
  {"webpack.config.staging.js",           iconSet.at("webpack")},
  {"webpack.config.staging.ts",           iconSet.at("webpack")},
  {"webpack.config.babel.js",             iconSet.at("webpack")},
  {"webpack.config.babel.ts",             iconSet.at("webpack")},
  {"webpack.config.base.babel.js",        iconSet.at("webpack")},
  {"webpack.config.base.babel.ts",        iconSet.at("webpack")},
  {"webpack.config.base.js",              iconSet.at("webpack")},
  {"webpack.config.base.ts",              iconSet.at("webpack")},
  {"webpack.config.staging.babel.js",     iconSet.at("webpack")},
  {"webpack.config.staging.babel.ts",     iconSet.at("webpack")},
  {"webpack.config.coffee",               iconSet.at("webpack")},
  {"webpack.config.test.js",              iconSet.at("webpack")},
  {"webpack.config.test.ts",              iconSet.at("webpack")},
  {"webpack.config.vendor.js",            iconSet.at("webpack")},
  {"webpack.config.vendor.ts",            iconSet.at("webpack")},
  {"webpack.config.vendor.production.js", iconSet.at("webpack")},
  {"webpack.config.vendor.production.ts", iconSet.at("webpack")},
  {"webpack.test.js",                     iconSet.at("webpack")},
  {"webpack.test.ts",                     iconSet.at("webpack")},
  {"webpack.dist.js",                     iconSet.at("webpack")},
  {"webpack.dist.ts",                     iconSet.at("webpack")},
  {"webpackfile.js",                      iconSet.at("webpack")},
  {"webpackfile.ts",                      iconSet.at("webpack")},
  {"ionic.config.json",                   iconSet.at("ionic")},
  {".io-config.json",                     iconSet.at("ionic")},
  {"gulpfile.js",                         iconSet.at("gulp")},
  {"gulpfile.mjs",                        iconSet.at("gulp")},
  {"gulpfile.ts",                         iconSet.at("gulp")},
  {"gulpfile.babel.js",                   iconSet.at("gulp")},
  {"package.json",                        iconSet.at("nodejs")},
  {"package-lock.json",                   iconSet.at("nodejs")},
  {".nvmrc",                              iconSet.at("nodejs")},
  {".esmrc",                              iconSet.at("nodejs")},
  {".node-version",                       iconSet.at("nodejs")},
  {".npmignore",                          iconSet.at("npm")},
  {".npmrc",                              iconSet.at("npm")},
  {".yarnrc",                             iconSet.at("yarn")},
  {"yarn.lock",                           iconSet.at("yarn")},
  {".yarnclean",                          iconSet.at("yarn")},
  {".yarn-integrity",                     iconSet.at("yarn")},
  {"yarn-error.log",                      iconSet.at("yarn")},
  {".yarnrc.yml",                         iconSet.at("yarn")},
  {".yarnrc.yaml",                        iconSet.at("yarn")},
  {"androidmanifest.xml",                 iconSet.at("android")},
  {".env.defaults",                       iconSet.at("tune")},
  {".env.example",                        iconSet.at("tune")},
  {".env.sample",                         iconSet.at("tune")},
  {".env.schema",                         iconSet.at("tune")},
  {".env.local",                          iconSet.at("tune")},
  {".env.dev",                            iconSet.at("tune")},
  {".env.development",                    iconSet.at("tune")},
  {".env.qa",                             iconSet.at("tune")},
  {".env.prod",                           iconSet.at("tune")},
  {".env.production",                     iconSet.at("tune")},
  {".env.staging",                        iconSet.at("tune")},
  {".env.preview",                        iconSet.at("tune")},
  {".env.test",                           iconSet.at("tune")},
  {".env.testing",                        iconSet.at("tune")},
  {".env.development.local",              iconSet.at("tune")},
  {".env.qa.local",                       iconSet.at("tune")},
  {".env.production.local",               iconSet.at("tune")},
  {".env.staging.local",                  iconSet.at("tune")},
  {".env.test.local",                     iconSet.at("tune")},
  {".babelrc",                            iconSet.at("babel")},
  {".babelrc.js",                         iconSet.at("babel")},
  {".babelrc.json",                       iconSet.at("babel")},
  {"babel.config.json",                   iconSet.at("babel")},
  {"babel.config.js",                     iconSet.at("babel")},
  {"contributing.md",                     iconSet.at("contributing")},
  {"readme.md",                           iconSet.at("readme")},
  {"readme.txt",                          iconSet.at("readme")},
  {"readme",                              iconSet.at("readme")},
  {"changelog",                           iconSet.at("changelog")},
  {"changelog.md",                        iconSet.at("changelog")},
  {"changelog.txt",                       iconSet.at("changelog")},
  {"changes",                             iconSet.at("changelog")},
  {"changes.md",                          iconSet.at("changelog")},
  {"changes.txt",                         iconSet.at("changelog")},
  {"credits",                             iconSet.at("credits")},
  {"credits.txt",                         iconSet.at("credits")},
  {"credits.md",                          iconSet.at("credits")},
  {"authors",                             iconSet.at("authors")},
  {"authors.md",                          iconSet.at("authors")},
  {"authors.txt",                         iconSet.at("authors")},
  {"favicon.ico",                         iconSet.at("favicon")},
  {"karma.conf.js",                       iconSet.at("karma")},
  {"karma.conf.ts",                       iconSet.at("karma")},
  {"karma.conf.coffee",                   iconSet.at("karma")},
  {"karma.config.js",                     iconSet.at("karma")},
  {"karma.config.ts",                     iconSet.at("karma")},
  {"karma-main.js",                       iconSet.at("karma")},
  {"karma-main.ts",                       iconSet.at("karma")},
  {".travis.yml",                         iconSet.at("travis")},
  {".codecov.yml",                        iconSet.at("codecov")},
  {"codecov.yml",                         iconSet.at("codecov")},
  {"protractor.conf.js",                  iconSet.at("protractor")},
  {"protractor.conf.ts",                  iconSet.at("protractor")},
  {"protractor.conf.coffee",              iconSet.at("protractor")},
  {"protractor.config.js",                iconSet.at("protractor")},
  {"protractor.config.ts",                iconSet.at("protractor")},
  {"procfile",                            iconSet.at("heroku")},
  {"procfile.windows",                    iconSet.at("heroku")},
  {".bowerrc",                            iconSet.at("bower")},
  {"bower.json",                          iconSet.at("bower")},
  {".eslintrc.js",                        iconSet.at("eslint")},
  {".eslintrc.cjs",                       iconSet.at("eslint")},
  {".eslintrc.yaml",                      iconSet.at("eslint")},
  {".eslintrc.yml",                       iconSet.at("eslint")},
  {".eslintrc.json",                      iconSet.at("eslint")},
  {".eslintrc",                           iconSet.at("eslint")},
  {".eslintignore",                       iconSet.at("eslint")},
  {".eslintcache",                        iconSet.at("eslint")},
  {"code_of_conduct.md",                  iconSet.at("conduct")},
  {"code_of_conduct.txt",                 iconSet.at("conduct")},
  {"mocha.opts",                          iconSet.at("mocha")},
  {".mocharc.yml",                        iconSet.at("mocha")},
  {".mocharc.yaml",                       iconSet.at("mocha")},
  {".mocharc.js",                         iconSet.at("mocha")},
  {".mocharc.json",                       iconSet.at("mocha")},
  {".mocharc.jsonc",                      iconSet.at("mocha")},
  {"jenkinsfile",                         iconSet.at("jenkins")},
  {"firebase.json",                       iconSet.at("firebase")},
  {".firebaserc",                         iconSet.at("firebase")},
  {"firestore.rules",                     iconSet.at("firebase")},
  {"firestore.indexes.json",              iconSet.at("firebase")},
  {".stylelintrc",                        iconSet.at("stylelint")},
  {"stylelint.config.js",                 iconSet.at("stylelint")},
  {".stylelintrc.json",                   iconSet.at("stylelint")},
  {".stylelintrc.yaml",                   iconSet.at("stylelint")},
  {".stylelintrc.yml",                    iconSet.at("stylelint")},
  {".stylelintrc.js",                     iconSet.at("stylelint")},
  {".stylelintignore",                    iconSet.at("stylelint")},
  {".codeclimate.yml",                    iconSet.at("code-climate")},
  {".prettierrc",                         iconSet.at("prettier")},
  {"prettier.config.js",                  iconSet.at("prettier")},
  {".prettierrc.js",                      iconSet.at("prettier")},
  {".prettierrc.json",                    iconSet.at("prettier")},
  {".prettierrc.yaml",                    iconSet.at("prettier")},
  {".prettierrc.yml",                     iconSet.at("prettier")},
  {".prettierignore",                     iconSet.at("prettier")},
  {"gruntfile.js",                        iconSet.at("grunt")},
  {"gruntfile.ts",                        iconSet.at("grunt")},
  {"gruntfile.coffee",                    iconSet.at("grunt")},
  {"gruntfile.babel.js",                  iconSet.at("grunt")},
  {"gruntfile.babel.ts",                  iconSet.at("grunt")},
  {"gruntfile.babel.coffee",              iconSet.at("grunt")},
  {"jest.config.js",                      iconSet.at("jest")},
  {"jest.config.ts",                      iconSet.at("jest")},
  {"jest.config.cjs",                     iconSet.at("jest")},
  {"jest.config.mjs",                     iconSet.at("jest")},
  {"jest.config.json",                    iconSet.at("jest")},
  {"jest.e2e.config.js",                  iconSet.at("jest")},
  {"jest.e2e.config.ts",                  iconSet.at("jest")},
  {"jest.e2e.config.cjs",                 iconSet.at("jest")},
  {"jest.e2e.config.mjs",                 iconSet.at("jest")},
  {"jest.e2e.config.json",                iconSet.at("jest")},
  {"jest.setup.js",                       iconSet.at("jest")},
  {"jest.setup.ts",                       iconSet.at("jest")},
  {"jest.json",                           iconSet.at("jest")},
  {".jestrc",                             iconSet.at("jest")},
  {".jestrc.js",                          iconSet.at("jest")},
  {".jestrc.json",                        iconSet.at("jest")},
  {"jest.teardown.js",                    iconSet.at("jest")},
  {"fastfile",                            iconSet.at("fastlane")},
  {"appfile",                             iconSet.at("fastlane")},
  {".helmignore",                         iconSet.at("helm")},
  {"makefile",                            iconSet.at("makefile")},
  {".releaserc",                          iconSet.at("semantic-release")},
  {".releaserc.yaml",                     iconSet.at("semantic-release")},
  {".releaserc.yml",                      iconSet.at("semantic-release")},
  {".releaserc.json",                     iconSet.at("semantic-release")},
  {".releaserc.js",                       iconSet.at("semantic-release")},
  {"release.config.js",                   iconSet.at("semantic-release")},
  {"bitbucket-pipelines.yaml",            iconSet.at("bitbucket")},
  {"bitbucket-pipelines.yml",             iconSet.at("bitbucket")},
  {"azure-pipelines.yml",                 iconSet.at("azure-pipelines")},
  {"azure-pipelines.yaml",                iconSet.at("azure-pipelines")},
  {"vagrantfile",                         iconSet.at("vagrant")},
  {"tailwind.js",                         iconSet.at("tailwindcss")},
  {"tailwind.config.js",                  iconSet.at("tailwindcss")},
  {"codeowners",                          iconSet.at("codeowners")},
  {".gcloudignore",                       iconSet.at("gcp")},
  {".huskyrc",                            iconSet.at("husky")},
  {"husky.config.js",                     iconSet.at("husky")},
  {".huskyrc.json",                       iconSet.at("husky")},
  {".huskyrc.js",                         iconSet.at("husky")},
  {".huskyrc.yaml",                       iconSet.at("husky")},
  {".huskyrc.yml",                        iconSet.at("husky")},
  {".commitlintrc",                       iconSet.at("commitlint")},
  {".commitlintrc.js",                    iconSet.at("commitlint")},
  {"commitlint.config.js",                iconSet.at("commitlint")},
  {".commitlintrc.json",                  iconSet.at("commitlint")},
  {".commitlint.yaml",                    iconSet.at("commitlint")},
  {".commitlint.yml",                     iconSet.at("commitlint")},
  {"dune",                                iconSet.at("dune")},
  {"dune-project",                        iconSet.at("dune")},
  {"roadmap.md",                          iconSet.at("roadmap")},
  {"roadmap.txt",                         iconSet.at("roadmap")},
  {"timeline.md",                         iconSet.at("roadmap")},
  {"timeline.txt",                        iconSet.at("roadmap")},
  {"milestones.md",                       iconSet.at("roadmap")},
  {"milestones.txt",                      iconSet.at("roadmap")},
  {"nuget.config",                        iconSet.at("nuget")},
  {".nuspec",                             iconSet.at("nuget")},
  {"nuget.exe",                           iconSet.at("nuget")},
  {"stryker.conf.js",                     iconSet.at("stryker")},
  {"stryker.conf.json",                   iconSet.at("stryker")},
  {".modernizrrc",                        iconSet.at("modernizr")},
  {".modernizrrc.js",                     iconSet.at("modernizr")},
  {".modernizrrc.json",                   iconSet.at("modernizr")},
  {"routing.ts",                          iconSet.at("routing")},
  {"routing.tsx",                         iconSet.at("routing")},
  {"routing.js",                          iconSet.at("routing")},
  {"routing.jsx",                         iconSet.at("routing")},
  {"routes.ts",                           iconSet.at("routing")},
  {"routes.tsx",                          iconSet.at("routing")},
  {"routes.js",                           iconSet.at("routing")},
  {"routes.jsx",                          iconSet.at("routing")},
};

}
