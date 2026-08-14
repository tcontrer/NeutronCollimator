## ********************************************************************
## * Author: Taylor Contreras                                         *
## * Date: 2026-09-12                                                 *
## * Description: Sorts the text output from Geant4, as the threads 
## *              since the output file of events to be out of order. *
## ********************************************************************


import numpy as np
import matplotlib.pyplot as plt

def sort_textgen_output(input_file, output_file):
    """
    Sorts the text output from Geant4 by event ID and writes the sorted data to an output file
    for use in the NOvA TextGen simulation.
    Args:
        input_file (str): Path to the input text file containing unsorted event data.
        output_file (str): Path to the output text file where sorted data will be written.
    """

    with open(input_file, 'r') as f:
        lines = f.readlines()

    # Parse the lines into a structured format
    events = {}
    numparticles = 0
    for line in lines:
        parts = line.strip().split(" ")
        if len(parts) < 3:
            continue
        event_id = int(parts[0])
        particle_data = parts[2:]

        # print(f"Event ID: {event_id}, Particle Data: {particle_data}")

        if event_id not in events:
            events[event_id] = [particle_data]
        else:
            events[event_id].append(particle_data)
        numparticles += 1


    # Sort the events by event ID
    sorted_event_ids = sorted(events.keys())
    print(f"Num of particles: {numparticles}")

    # Write the sorted data to the output file
    with open(output_file, 'w') as f:
        for event_id in sorted_event_ids:
            particles = events[event_id]
            f.write(f"{event_id} {len(particles)}\n")
            for particle in particles:
                f.write(" ".join(particle) + "\n")

def plot_event_distribution(input_file):
    """
    Plots the distribution of events and particle positions.
    Args:
        input_file (str): Path to the input text file containing event data.
    """
    with open(input_file, 'r') as f:
        lines = f.readlines()

    event_ids = []
    xs = []
    ys = []
    zs = []
    for line in lines:
        parts = line.strip().split(" ")
        if len(parts) < 3:
            continue
        event_id = int(parts[0])
        event_ids.append(event_id)
        xs.append(float(parts[-4]))
        ys.append(float(parts[-3]))
        zs.append(float(parts[-2]))

    # Count the occurrences of each event ID
    unique_event_ids, particles_per_event = np.unique(event_ids, return_counts=True)

    # Plot the particles per event distribution
    plt.hist(particles_per_event)
    plt.xlabel('Particles per Event')
    plt.ylabel('Number of Events')
    plt.title(f"Total Events: {len(particles_per_event)}, Total Particles: {len(event_ids)}")
    plt.savefig('particles_per_event_distribution.png')
    plt.close()

    # Plot the 1D distribution of x, y, z coordinates
    plt.figure(figsize=(12, 4))
    plt.subplot(1, 3, 1)
    plt.hist(xs, bins=100)
    plt.xlabel('x')
    plt.ylabel('Number of Particles')

    plt.subplot(1, 3, 2)
    plt.hist(ys, bins=100)
    plt.xlabel('y')
    plt.ylabel('Number of Particles')

    plt.subplot(1, 3, 3)
    plt.hist(zs, bins=100)
    plt.xlabel('z')
    plt.ylabel('Number of Particles')

    plt.tight_layout()
    plt.savefig('particle_pos_distribution.png')
    plt.close()

    # Plot 2D xy distribtuion
    plt.figure(figsize=(6, 6))
    plt.hist2d(xs, ys, bins=100)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.colorbar(label='Number of Particles')
    plt.savefig('particle_pos_distribution_xy.png')
    plt.close()

    return


if __name__ == "__main__":
    input_file = "textgen_output.txt"
    #input_file = "sorted_textgen_output_nocoll.txt"
    output_file = "sorted_textgen_output.txt"
    sort_textgen_output(input_file, output_file)
    plot_event_distribution(input_file)