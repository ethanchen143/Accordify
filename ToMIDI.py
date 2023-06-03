import music21

def chord_progression_to_midi(chord_prog_string, output_filename):
    # Parse the chord progression string into a list of chords
    chords = [music21.harmony.ChordSymbol(c) for c in chord_prog_string.split()]

    # Create a stream to hold the chord progression
    chord_stream = music21.stream.Stream()

    # Add each chord to the stream
    for chord in chords:
        chord.duration = music21.duration.Duration('whole')
        chord_stream.append(chord)

    # Add a piano instrument to the stream
    piano = music21.instrument.Piano()
    chord_stream.insert(0, piano)

    # Set the time signature and tempo
    chord_stream.insert(0, music21.meter.TimeSignature('4/4'))
    chord_stream.insert(0, music21.tempo.MetronomeMark(number=120))

    # Create a MIDI file from the chord stream
    midi_file = music21.midi.translate.streamToMidiFile(chord_stream)

    # Save the MIDI file to disk
    midi_file.open(output_filename, 'wb')
    midi_file.write()
    midi_file.close()

def main():
    chord_prog_string = 'Cmaj7 D7 G7 Cmaj7'
    output_filename = 'chord_progression.mid'
    chord_progression_to_midi(chord_prog_string, output_filename)

if __name__ == "__main__":
    main()