# TASDK Android #

TASDK (TelenavAutomotive SDK) is a collection of Android modules, ready to be integrated into client apps. The Android modules are wrappers over
C++ modules. They provide higher levels apis, which ease integration into Android apps.


----
## Prerequisites ##

1. Install [Android Studio 3.2.0](https://developer.android.com/studio/archive)
(click 'I agree' btn in order to see the archived versions)
2. From _Android Studio->Preference->Plugins->Browse Repositories_, install the _SonarQube community plugin_


----
## Setup ##

This repo contains both Java & C++ code, required for the JNI layer. Whenever building a module,
the Java & C++ sources are linked and build together in the resulting '.aar'.

### Setup on OSX ###

* Open a terminal window
```bash
$ cd <path_to_tasdk>
$ sh setup/osx/osx_tasdk_android_ndk_setup.sh
$ ./gradlew clean build
```


### Setup on Windows ###

The project setup is configured by default for Mac system operation. In order to build and run the project on Windows the following steps must be followed:

* Install **CMAKE** (version 3.11) and add it to system environment variables.
* Install **Python** (version 2.7) and add it to system environment variables.
* Install **android-ndk-r15c** from https://developer.android.com/ndk/downloads/older_releases
* Comment out in **build.gradle** the `downloadJniDependencies` task.
* Get a Windows port of GNU Make. Android NDK r7 (and newer) already has `make.exe` on board so just add path to your `make.exe` to system PATH:
    * In Android Studio terminal run **PATH=%PATH%;path-to-make-exe**, (e.g. PATH=%PATH%;C:\Users\ioanac\AppData\Local\Android\Sdk\ndk-bundle\prebuilt\windows-x86_64\bin).
* Download the C++ dependencies:
    * In Android Studio terminal run **python build.py -t android-ndk-r15c --configuration=armv7a**
    * Even though this command will result in failure the download should be successful and `modules` folder should contain the TASDK C++ dependencies.
* Change the path to **ndk-bundle** in `..\modules\win32\toolchains\android-14-ndk-r15c-armv7a.cmake`:
    * Replace the line bellow `# SET (CMAKE_ANDROID_NDK /opt/tools/android-sdk-linux/ndk-bundle)` line to your NDK path (e.g. SET (CMAKE_ANDROID_NDK C:/Users/ioanac/AppData/Local/Android/Sdk/ndk-bundle)).
* Resolve compiler issues:
    * Open `..\modules\android-ndk-r15c\include\stdio.h` and add **#include_next <stdio.h>** as first statement (it should be before `#ifndef	_STDIO_H_`).
    * Open `..\modules\android-ndk-r15c\include\unistd.h` and add **#include_next <unistd.h>** as first statement (it should be before `#ifndef _UNISTD_H_`).
* Run **build.py** again, this time including the `skip-update` option to avoid downloading the dependencies again:
    * In Android Studio terminal run **python build.py -t android-ndk-r15c --configuration=armv7a --skip-update**
* Move **libMerged.so** that was generated at the previous step under `/build/TasdkJni-android-ndk-r15c/armv7a/` to `android-sdk-common/src/main/jniLibs/armeabi-v7a`.
* From a terminal window: `cd <path_to_tasdk_android>`
* Run: `./gradlew clean build`


----
## Development ##

### Coding standards ###

The project follows the [Java coding standards](https://google.github.io/styleguide/javaguide.html)

### Branching strategy ###

The project's main branch is **master**. It is the branch used for releases.
The main development is done into **develop** branch.

#### Feature branch (Epic branch)
* **feature** branches are created from **develop**.
* they start with the JIRA Epic's id & summary. All feature branches should be under `origin/feature`. E.g. `origin/feature/TASDK-65-navigation-sdk`
* **feature** branches get merged into **develop**, NOT **master**
* before merging the **feature** into **develop** do a merge from **develop**->**feature branch**
* after the 'develop'->'feature branch' merge, build & run the tests. If **feature** Jenkins jobs are available, ensure the jobs build successfully
* create a pull request for merging **feature** branch into develop

#### Task branch
* if the corresponding jira task **has an epic**:
 * create the **task** branch from the **feature** branch, under `origin/tasks/<jira_epic_id>/`. E.g. `origin/tasks/TASDK-65/TASDK-245-android-routing-high-level-apis`
* if the corresponding jira task **DOESN'T have an epic**:
 * create the **task** branch from **develop**, under `origin/tasks/` E.g. `origin/tasks/TASDK-245-android-routing-high-level-apis`
* before merging the **task** branch do a merge with the branch it was created from
* ensure it builds & tests pass
* merge the **task** branch into the branch it was created from

#### Bugfix branch
* create a branch from **develop**
* **bugfix** branches' name start with `origin/bugfix`. E.g. `origin/bugfix/TASDK-1603-android-great-bug`
* before merging the **bugfix** branch, do a merge with the branch it was created from
* ensure it builds & tests pass
* merge the **bugfix** branch into the branch it was created from


### Commit messages ###
* Each commit should respect the following pattern: `<jira_id>: [<platform>: ] <commit_message>`. E.g. `TASDK-3244: JNI: update 1.038`

----
## Writing tests ##

For Android there are 2 main categories of tests:

* Unit tests: require just the JAVA apis, and are mainly used for testing simple methods which receive and input and return a testable output
* Instrumented tests: tests using the Android apis. They are used for testing JNI & integration cases on real devices.

#### Unit Tests
* found under each module's `src/test` folder
* each unit test will end with `...Test`.

#### Instrumented Tests
* in order for instrumented tests to pass, they need a valid path to a map data folder.
The paths need to be set inside the main gradle.properties file (`naMapDataPath`, `euMapDataPath` properties)
* found under each module's `src/androidTest` folder
* each instrumented test will end with `...InstrumentedTest`.


----
## How to copy Maps on device  ##
* download the map data, depending on the region you want to test against (North America - NA, Europe - EU, China - CH).
 * Default Tasdk [NA maps]( http://tactaws.telenav.com.s3-us-west-2.amazonaws.com/ec_latest_builds/DENALI_CLIENT/NA_Here_17Q3/Here_17Q3_NA_201805140102/Denali_Here_17Q3_NA_201805140102.tar.gz)
 * Default Tasdk [EU maps]( https://s3-eu-west-1.amazonaws.com/qa-eu/ec_latest_builds/DENALI_CLIENT/EU_Here_18Q1/Here_18Q1_EU_201811181915/Denali_Here_18Q1_EU_201811181915.tar.gz)
 * [Denali maps](https://spaces.telenav.com:8443/display/auto/Data+Release+Archive%3A+Denali+Info+3.5)
* ensure android sdk path is added inside ~./bash_profile in order to use `adb`. (adding android sdk path is not part of this scope)
* copy the map data on the device, using **adb push**
```bash
$ adb push <map_data_path_from_local_machine> /mnt/sdcard/
```


----
## How to set env to build JNI in AndroiStudio  ##
* Taken `android-ndk-r51c` as an example:
 * set `build_jni_locally=true` in `gradle.properties`
 * add `ndk.dir=/opt/android-ndk-r15c` in `local.properties`


----
## Who do I talk to? ###

* Igor Gritco (JNI dev): [igor.gritco@telenav.com](mailto:igor.gritco@telenav.com)
* Alex Deaconu (Android dev): [alexandru.deaconu@telenav.com](mailto:alexandru.deaconu@telenav.com)
* Cristian Pintea (Android dev): [cristian.pintea@telenav.com](mailto:cristian.pintea@telenav.com)
* Catalin Muresan (Android dev): [catalin.muresan@telenav.com](mailto:catalin.muresan@telenav.com)
* Maria Hapa (Android dev): [maria.hapa@telenav.com](mailto:maria.hapa@telenav.com)
