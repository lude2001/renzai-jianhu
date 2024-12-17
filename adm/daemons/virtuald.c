// virtuald.c
//
// This object is the virtual object server of ES2 mudlib.
//
// By Annihilator (07/06/95)
// Adapted for XKX (12/15/95)

void create()
{
	seteuid(getuid());
}

// This function is called by master object to return the "virtual" object
// of <file> when dirver failed to find such a file.
mixed compile_object(string file)
{
	string virtual;
    object ob;
    int x, y, z, m, n;


	if (!sscanf(file, "/xuni/%*s", file))
	return 0;

    n = strsrch(file, "/", -1);
    if (n < 1)
    {
        return 0;
    }

    virtual = file[0..n - 1];

    if (file_size(virtual + ".c") < 1)
    {
        return 0;
    }

    if ((m = sscanf(file[n + 1..], "%d,%d,%d", x, y, z)) != 3)
    {
        if ((m = sscanf(file[n + 1..], "%d,%d", x, y)) != 2)
        {
            return 0;
        }
    }

    if (m == 2 && !(ob = new (virtual, x, y)))
    {
        return 0;
    }
    else if (m == 3 && !(ob = new (virtual, x, y, z)))
    {
        return 0;
    }

    return ob;
}
