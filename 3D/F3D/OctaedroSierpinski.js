import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

camera.position.z = 4;

function createOctahedronFractal(size, depth) {
    const group = new THREE.Group();
    
    if (depth === 0) {
        const geometry = new THREE.OctahedronGeometry(size);
        const material = new THREE.MeshBasicMaterial({ color: 0x0000ff, wireframe: true });
        const octahedron = new THREE.Mesh(geometry, material);
        group.add(octahedron);
    } else {
        const newSize = size / 2;
        
        const positions = [
            [newSize, 0, newSize],
            [-newSize, 0, newSize],
            [newSize, 0, -newSize],
            [-newSize, 0, -newSize],
            [0, newSize, newSize],
            [0, -newSize, newSize],
            [0, newSize, -newSize],
            [0, -newSize, -newSize]
        ];

        for (const pos of positions) {
            const subFractal = createOctahedronFractal(newSize, depth - 1);
            subFractal.position.set(...pos);
            group.add(subFractal);
        }
    }

    return group;
}

const fractal = createOctahedronFractal(1, 0);
scene.add(fractal);

function animate() {
    //fractal.rotation.x += 0.01;
    fractal.rotation.y += 0.01;
    renderer.render(scene, camera);
}
