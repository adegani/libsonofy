# Harmony related utilities
## sonofy_chord
Chord generation and transformation
- inversion
- mode
- translate (shift root)
- transpose (shift in scale, it can change the root)
- alterate
- getNotes
- getPitchClasses
- setRoot (A4)
- setPitchClass (A)
- setKey (works as a "filter" on the possibile notes)
- getOctave
- setOctave

##sonofy_interval
Intervals utilities
- naming: getInterval( distanceInSemitones )
- getDistance in semitones (interval1, interval2)

##sonofy_key
Key manipulation utilities
- relative
- parallel
- modulate (semitones)
- setMode
- setRootNote
- setRootPitchClass

##sonofy_note
Note level utilities
- getNote A4, ...
- getPitchClass A,...
- shift (semitones, intervals, deegrees of a scale)
- setNote
- getOctave
- setOctave

##sonofy_scale.h
Scale generation and transformation
- getNoteFromDegrees
- getPitchClasseFromDegrees
- setRoot
- setPitchClass
- setType (modes and other particular scales)
