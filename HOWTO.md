OK, how could the sources be (re)created like this?
---------------------------------------------------

To begin with, if you ever consider doing similar work, you shall be warned.
I mean, *really*, warned.

- Let's begin with the fact that as of writing this, only code originally
built with Borland C++ 2.0, 3.0 or 3.1 is covered. While there's also
code originally built with Watcom, this is *not* covered here, but
hopefully the notes should still give the right ideas.
- Please note that if you add or remove even just one byte to/from a single
function, the locations of all functions following it will probably change
as a consequence. This also means that any *earlier* reference to such
a function (e.g., a function call) will be modified. This can often lead
to changes scattered around *the whole EXE*.
- The same applies if you add/remove chars to/from a string, or add/remove
a global/static variable.
- However, as long as the changes are simple and few, there are good chances
you may scan the two EXEs, as long as there is common binary code, until you
get to (virtually) total mismatches.
- From here, it's a matter of identifying the relevant code piece in the
sources and then making changes as required. You can use ifdefs to mark the
different versions.
- Afterwards, build using the right compiler (specific Borland C++ version).
Make sure the project is clean i.e., there are no OBJ files scattered around,
with the possible exception of data OBJ files (like the Wolf3D palette).
- At this point, both EXEs can be compared, assuming they're unpacked in
*the exact same way*. For instance, if LZEXE91 was originally used, then
the newly built EXE shall first be packed with LZEXE91, and then unpacked.
- Translating the EXEs' binary code to assembly will almost surely assist.
Doing more can assist, too.
- IDA Pro was originally used while comparing various EXEs. A freeware version
(v5.0) can be used.
- If virtually all the code is the same, including the offsets of variables
(or automatically generated names of them), it should be possible to create
ASM code and then do a simple textual comparison. A binary comparison of
the EXEs is also a possibility, if one desires for any reason.
- Remember, though, that it'll only work well if *nothing* is different
before any actual code different you want to locate.
- Then again, even if various variables' offsets differ, you can still create
a textual diff. You just need to live with the fact that variable names are
expect to differ, and look for an *actual* difference in the codebase.

Now, have I already said you shall be warned?
Because this can be *highly addicting*. No, I seriously mean it.

This is especially the case as long as it's more-or-less clear which changes
should be done, so it all feels kind of "automatic" (and thus, addicting).

Let's emphasize that the exact way in which the EXEs were built matters.

- The version of Borland C++ shall be chosen wisely. It has to be the *exact*
same version originally used.
- Also, surprisingly enough, there *are* minor differences in the outputs
of LZEXE versions 0.91 and 0.91e (for a common input EXE). There may be
similar side-effects with other EXE packers (and unpackers).
- The Borland C++ project shall be setup in more-or-less the same way.
This includes the order in which source and object files appear,
as well as various project settings: Optimizations, other compiler settings,
and more, including even debugger settings (e.g., "Source Debugging").
- For one exception to this, you'll probably want to enable creation
of .MAP file with as much information as possible. In such a case,
it should cover all non-static functions and variables.
- Also, it should probably be safe to change stuff like output directories
as you wish.
- If there's any external data OBJ file being linked, then merely shuffling
it around in the project's files list is not necessarily sufficient. Don't
forget you may want to use a different object file (e.g., a different palette).
- Also, for each such object, you may have to check if the object's data
was originally a part of the data segment, or rather resided in a separate
segment. You may have to recreate a new object for this reason, even if the
data it consists of is exactly the same as previously used.
- Note that this is a property of the *object* file, and *not* of
the Borland C++ project file.

I'm reminding again, this can be addicting!

Let's list a few more facts, at least for games like Wolfenstein 3D. Some
of these can show how important it is to know about the way the original EXE
was built as much as possible; And hopefully, any original source release,
even if for a different revision, shall greatly assist.

- The following depends on the memory model originally in use. In the case
of Wolfenstein 3D, each compiled or assembled compilation unit should
match a segment in the EXE.
- The very first segment in Wolf3D consists of C0.ASM, which apppears to be
a modification of a source library file from Borland C++ 3.0 (or related).
- The second segment in Wolf3D (but not consists of H_LDIV.ASM, also based on
a Borland C++ library source file (if not identical to). An exception to this
is S3DNA (the 1996 "v1.0" release), for which the EXE has H_LDIV code, but
the H_LDIV.ASM file is not explicitly included in the project's files list.
- Just like S3DNA, other games may use just one of these (explicitly), if any.


On to the next list:

- Tracking the functions isn't very difficult. Basically, the order in which
functions are defined in a compilation unit (e.g., C or ASM file) is retained
in the built EXE. When it comes to different compilation units, they shall
be ordered as listed in the project.
- Unfortunately, though, things are more complicated when it comes to
global and static variables. It does look like variables can be grouped
in the EXE, based on properties of them, but it can be quite difficult
to predict how will they be exactly ordered.
- Examples of such properties: Static vs. non-static, implicitly initialized
to 0 vs. explicitly initialized.
- The type of the variables (and/or their sizes) may have a part, too.
- Even by simply declaring a small list of variables with "extern"
(when not required), you can change the way in which at least one
of them gets located in the EXE!
- If there's some a bizarre gap of data, then maybe there's an unused variable.
Either that, or it wasn't probably marked and you need to manually locate
a reference to it (e.g., the offset in the segment in which it resides).

A few more examples of how minor things matter:

- Deleting code, or making simple changes, is one thing, but recreating code
you don't have access to can be more difficult. Maybe, however, you'll have
some luck and the code is already there in some form (possibly modified);
It might be in another location (heard about copying-and-pasting),
and/or commented out.
- Also, if you want to skip some difficult-to-figure code piece while still
making later function offsets correct, you can try add to add unused code
(e.g., a sequence of ASM NOPs) as a placeholder.
- Using a defined enum value vs. an integer literal can make
minor differences. Watch out, since macros may cover these up.
It actually happened while recreating code for Wolfenstein 3D v1.0
(AUDIOWL6.H and, possibly, CA_LoadAllsounds)
- There was even a case, while recreating the S3DNA DOS EXE, in which *spacing*
mattered (in the function PlayerProjectileTryMove). Luckily, the original EXE
EXE still has debugging symbols, so it can be inspected with Turbo Debugger,
showing original line numbers. As in the function TryMove, some if condition
was initially split into two lines. Turns how, it actually "compressed"
to a single line of code in S3DNA.

To finish:

- I could write some more tips, if I recalled any. However, it's probably
better to let you try to figure out things on your own!
- Remember, it's still possible to fail. As of writing this, I failed to
faithfully re-create the Catacomb v1.24 EXE, last time I tried. It is weird
that it's a bit different from what's there in the released code, which is
supposedly for v1.24. Reason is, other than this code piece, as ewll as a
weirdly different STARTTILE8 value in GFXE_ABS_H (but NOT in GFXE_ABS.EQU),
the code's behaviors are essentially the same as the original's.
- As of writing this, for a few recreated versions of Spear of Destiny,
there is weirdly the need to delete a single OBJ file after initially
building an EXE, and then re-launch Borland C++, re-building the
OBJ and ultimately the final output EXE (before e.g., packing, if desired).

NY00123
