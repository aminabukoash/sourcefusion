# Supported Operating Systems

This software has been tested with Windows and Unix Platforms.

Windows:
* Windows 8 (64-bit)
* Windows 10 (64-bit)

macOS:
* macOS High Sierra
* macOS Mojave
* macOS Catalina

Linux:
* Kali Linux
* Ubuntu 18

# Dependencies

Following are the requirements to run this software:

* GNU Make
* GCC
* GSL(GNU Scientific Library) Version 2.6

# Compilers

This software has been built using these compilers:

* gcc (7.4.0)
* Apple clang (11.0.0)

# Dependency Installation
**Windows**<br>
All dependencies for the Windows Platform was installed through **Cygwin** find the steps to install it below.

## Steps

1. Download the cygwin from https://cygwin.com/install.html
	>Download the 64-bit .exe

2. Run the setup file. Click Next.

3. Select "Install from internet" and click next.

4. Select your C:\ root directory for storage of Cygwin files and click next.

5. Choose your preferred directory for storage of Cygwin local package directory and click next.
   Remember both these locations as they might be required for installing more libraries later.

6. Click next.You need to choose a mirror to download Cygwin. Choose any mirror and click next

7. Select the Packages now and latter on you can install the additional package as well.

8. Click on search box and look for following packages:
	* make (Under Devel )
	* gcc-core (Under Devel category)
	* libgsl-devel (Under Libs category)
	* gsl (Under Science category)

9. Click on Next. All the packages along with its dependencies will be downloaded.

**macOS**<br>
To install the gsl library on macOS, simply use 'brew' and run the following command.
````cmd
brew install gsl
````
**Linux**<br>
To install the gsl library on Linux, simply use the 'apt-get' command as a super user and run the following command.
````cmd
sudo apt-get install gsl
````
# Compiling and Running the Project
We use GNU make to build the project.<br>
**Main Software**
````cmd
make
````
**Test**
````cmd
make tests
````

**Entire Project**
````cmd
make all
````
The compiled binaries can be found in the 'bin' directory<br>
Refer to the doc/user_guide.pdf file on how to use the software