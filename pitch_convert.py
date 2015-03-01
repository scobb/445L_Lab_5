__author__ = 'scobb'


def main():
    bus = 80000000
    per_wave = 32
    freq = 131 / 2
    octave = 2
    pitches = ['C', 'Dflat', 'D', 'Eflat', 'E', 'F', 'Gflat', 'G', 'Aflat', 'A', 'Bflat', 'B']
    while octave < 7:
        for i, pitch in enumerate(pitches):
            this_freq = freq * 2**(i/12)
            print('#define %s%d %d' % (pitch, octave, bus / (this_freq * per_wave)))
        freq *= 2
        octave += 1


if __name__ == '__main__':
    main()