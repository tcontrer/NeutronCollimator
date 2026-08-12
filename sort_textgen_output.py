import numpy as np

def sort_textgen_output(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    # Parse the lines into a structured format
    events = {}
    for line in lines:
        parts = line.strip().split()
        if len(parts) < 3:
            continue
        event_id = int(parts[0])
        particle_data = parts[2:]

        # print(f"Event ID: {event_id}, Particle Data: {particle_data}")

        if event_id not in events:
            events[event_id] = [particle_data]
        else:
            events[event_id].append(particle_data)

    # Sort the events by event ID
    sorted_event_ids = sorted(events.keys())
    #print(f"Sorted Event IDs: {sorted_event_ids}")

    # Write the sorted data to the output file
    with open(output_file, 'w') as f:
        for event_id in sorted_event_ids:
            particles = events[event_id]
            f.write(f"{event_id} {len(particles)}\n")
            for particle in particles:
                f.write(" ".join(particle) + "\n")

if __name__ == "__main__":
    input_file = "textgen_output.txt"
    output_file = "sorted_textgen_output.txt"
    sort_textgen_output(input_file, output_file)