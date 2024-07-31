import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

camera.position.z = 5;

function createPythagorasTree(size, depth) {
    const group = new THREE.Group();

    if (depth === 0) {
        const geometry = new THREE.BoxGeometry(size, size, size);
        const edges = new THREE.EdgesGeometry(geometry);
        const material = new THREE.LineBasicMaterial({ color: 0x8B4513 });
        const line = new THREE.LineSegments(edges, material);
        group.add(line);
    } else {
        const newSize = size / 2;

        const baseGeometry = new THREE.BoxGeometry(size, size / 2, size / 2);
        const baseEdges = new THREE.EdgesGeometry(baseGeometry);
        const baseMaterial = new THREE.LineBasicMaterial({ color: 0x8B4513 });
        const base = new THREE.LineSegments(baseEdges, baseMaterial);
        group.add(base);

        const leftBranch = createPythagorasTree(newSize, depth - 1);
        leftBranch.position.set(-newSize / 2, newSize / 2, 0);
        leftBranch.rotation.z = Math.PI / 4;
        group.add(leftBranch);

        const rightBranch = createPythagorasTree(newSize, depth - 1);
        rightBranch.position.set(newSize / 2, newSize / 2, 0);
        rightBranch.rotation.z = -Math.PI / 4;
        group.add(rightBranch);
    }

    return group;
}

const fractal = createPythagorasTree(4, 5);
//fractal.position.y = -5;
scene.add(fractal);

function animate() {
    //fractal.rotation.x += 0.01;
    fractal.rotation.y += 0.01;
    renderer.render(scene, camera);
}
