# Address-Scaling
Address-Scaling: Architectural Support for Fine-grained Thread-safe Metadata Management

### Repository setup

```sh
git subtree add --prefix gem5-source https://gem5.googlesource.com/public/gem5 v21.2.1.0 --squash
```

https://www.gem5.org/getting_started/

### Installing dependencies

```sh
sudo apt install -y python3 python3-six python-is-python3 python3-pydot
```

### Setting up the python3 virtualenv

```sh
python3 -m venv py3venv
source ./py3venv/bin/activate
```

When you want to go back to using your system python installation, you can run

```sh
deactivate
```

#### Installing python3 dependencies

We now want the up-to-date dependencies for building and running gem5. So, we
need to install the following **within our virtual environment**.

```sh
pip install scons pydot
```

### Building gem5

```sh
cd gem5-source
scons build/X86/gem5.opt -j$(nproc)
# For debugging
scons build/X86/gem5.debug -j$(nproc)
# or
scons build/X86_MESI_Two_Level/gem5.opt -j$(nproc)
```
