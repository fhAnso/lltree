CC = gcc

SRCDIR = src
BUILDDIR = build
BINDIR = bin
INSTALLDIR = /usr/local/bin

TARGET = lltree

# Source files of the project
SOURCES = $(SRCDIR)/lltree.c $(SRCDIR)/utils.c

# Object files corresponding to the source files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Build the target executable from the object files
$(BINDIR)/$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@

# Build object file from source
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Create bin directory if it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Install the target executable to the install directory
install: $(BINDIR)/$(TARGET)
	sudo mv $(BINDIR)/$(TARGET) $(INSTALLDIR)

uninstall: $(INSTALLDIR)/$(TARGET)
	sudo rm $(INSTALLDIR)/$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: uninstall install clean
